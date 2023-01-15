#include "Aiguilleur.h"

Aiguilleur::Aiguilleur(std::string name)
{
	m_name += name;

	std::cout << "Vous etes : " << m_name << std::endl;
}

void Aiguilleur::addServer(std::string serverName, const int port)
{
	sf::TcpSocket* socket = new sf::TcpSocket;

	if (socket->connect(serverName, port) == sf::Socket::Done)
	{
		std::cout << "Vous avez pu vous connecter au serveur : " << serverName << " - " << port << std::endl;
		m_servers.push_back(socket);
	}
	else
	{
		std::cout << "Vous n'avez pas pu vous connecter au serveur : " << serverName << " - " << port << std::endl;
		delete socket;
	}
}


sf::TcpSocket* Aiguilleur::getServer()
{
	// On choisit le serveur en prennant celui qui est après celui qui vient d'être utilisé

	sf::TcpSocket* server = m_servers[iRepartiteur];

	iRepartiteur++;

	// On évite l'out of range et on retourne au début du tableau

	if (iRepartiteur > m_servers.size() - 1)
	{
		iRepartiteur = 0;
	}

	return server;
}

void Aiguilleur::traitReponse(sf::TcpSocket* socket, std::string response)
{

	// on prend les 3 premiers caractères pour connaître la commande 

	std::string command = response.substr(0, 3);

	const int responseLength = response.length();

	// si la réponse fait moins de 5 caractères alors elle est invalide
	 
	if (responseLength < 5)
	{
		this->sendMessage(socket, "Requete invalide !");
	}
	else if (command == "get")
	{
		std::cout << "Get de : " << socket << std::endl;

		std::string file = response.substr(4, responseLength - 4);

		std::cout << "Il veut lire : " << file << std::endl;

		// On envoie la requête au serveur choisi selon la répartition de charge

		sf::TcpSocket* server = getServer();

		this->sendMessage(server, file);

		Packet responseMachine = this->receiveMessage(server);
		
		if (responseMachine.status == sf::Socket::Done)
		{
			this->sendMessage(socket, responseMachine.message);
		}
		else
		{
			std::cout << "Pb connexion serveur : " << server << std::endl;
			this->sendMessage(socket, "Pb connexion serveur");
		}

	}
	else
	{
		std::string error = "Commande : " + command + " inconnue !";
		std::cout << error << std::endl;
		this->sendMessage(socket, error);
	}
}

void Aiguilleur::listenPort(const int port)
{

	// bind the listener to a port
	if (m_listener.listen(port) != sf::Socket::Done)
	{
		std::cout << "Impossible d'ecouter le port " << port << std::endl;
	}
	else
	{

		std::cout << m_name << " est en train d'ecouter sur le port " << port << std::endl;

		m_socketSelector.add(m_listener);

		while (true)
		{

			// Make the selector wait for data on any socket
			if (m_socketSelector.wait(sf::microseconds(100)))
			{
				// Test the listener
				if (m_socketSelector.isReady(m_listener))
				{
					// The listener is ready: there is a pending connection
					sf::TcpSocket* client = new sf::TcpSocket;

					if (m_listener.accept(*client) == sf::Socket::Done)
					{

						m_socketSelector.add(*client);

						m_clients.push_back(client);

						std::cout << "Un nouveau client a ete ajoute : " << client << std::endl;

						this->sendMessage(client, "Vous etes connecte !");
						this->sendMessage(client, "--- COMMANDES : ---");
						this->sendMessage(client, "get <fichier> : pour recevoir un fichier");
						this->sendMessage(client, "stop : pour se connecter");


					}
					else
					{
						// Error, we won't get a new connection, delete the socket
						std::cout << "Erreur nouvelle connexion client" << std::endl;
						delete client;
					}
				}
				else
				{
					// The listener socket is not ready, test all other sockets (the clients)

					for (int i = 0; i < m_clients.size(); i++)
					{
						sf::TcpSocket* client = m_clients[i];

						if (m_socketSelector.isReady(*client))
						{

							Packet resp = this->receiveMessage(client);

							if (resp.status == sf::Socket::Status::Done)
							{
								std::cout << client << " : " << resp.message << std::endl;

								this->traitReponse(client, resp.message);
							}
							else // Si le client s'est deconnecté on le retire
							{
								std::cout << "Le client : " << client << " s'est deconnecte !" << std::endl;

								m_socketSelector.remove(*client);
								client->disconnect();
								m_clients.erase(m_clients.begin() + i);
								i--;
							}

						}
					}

				}
			}

		}
	}
}
