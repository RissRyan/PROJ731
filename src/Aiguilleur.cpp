#include "Aiguilleur.h"

void Aiguilleur::addServer(Server* server)
{
	m_servers.push_back(server);
}

void Aiguilleur::traitReponse(sf::TcpSocket* socket, std::string response)
{
	std::string command = response.substr(0, 3);

	std::cout << command << std::endl;

	const int responseLength = response.length();
	 
	if (responseLength < 5)
	{
		this->sendMessage(socket, "Requete invalide !");
	}
	else if (command == "get")
	{
		std::cout << "Get from : " << socket << std::endl;

		std::string flag = response.substr(4, responseLength - 4);

		std::cout << "He wants to get : " << flag << std::endl;

		Data* gotData = m_servers[0]->getData(flag);
		
		if (gotData != nullptr)
		{
			this->sendMessage(socket, gotData->data);
		}
		else
		{
			this->sendMessage(socket, "Ce fichier n'existe pas !");
		}

	}
	else
	{
		std::string ok = "Commande : " + command + " inconnue !";
		std::cout << ok << std::endl;
		this->sendMessage(socket, ok);
	}
}

void Aiguilleur::listenPort()
{

	// bind the listener to a port
	if (m_listener.listen(53000) != sf::Socket::Done)
	{
		std::cout << "Bababoey\n";
	}

	m_socketSelector.add(m_listener);

	while (true)
	{

		//std::cout << "Nb de clients : " << clients.size() << std::endl;

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

					this->sendMessage(client, "Vous êtes connecte !");


				}
				else
				{
					// Error, we won't get a new connection, delete the socket
					std::cout << "Erreur connexion" << std::endl;
					delete client;
				}
			}
			else
			{
				// The listener socket is not ready, test all other sockets (the clients)

				for (int i = 0; i < m_clients.size(); i++)
				{
					sf::TcpSocket* client = m_clients[i];
					std::cout << client << std::endl;
					
					if (m_socketSelector.isReady(*client))
					{
						
						Packet resp = this->receiveMessage(client);

						if (resp.status == sf::Socket::Status::Done)
						{
							std::cout << client->getRemoteAddress() << " : " << resp.message << std::endl;

							this->traitReponse(client, resp.message);
						}
						else
						{
							std::cout << "Le client : " << client << " s'est déconnecté !" << std::endl;

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
