#include "Aiguilleur.h"

void Aiguilleur::addServer(Server* server)
{
	m_servers.push_back(server);
}

void Aiguilleur::traiterReponse(std::string response)
{
	std::cout << response.substr(0, 3) << std::endl;
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
						
						std::string resp = this->receiveMessage(client);

						std::cout << client->getRemoteAddress() << " : " << resp << std::endl;

						if (resp == "[RECEIVE] Disconnected\n")
						{
							std::cout << "Ok on fait ca" << std::endl;

							m_socketSelector.remove(*client);
							client->disconnect();
							m_clients.erase(m_clients.begin() + i);
							i--;
						}

						//this->traiterReponse(resp);
					}
				}


			}
		}

	}
}
