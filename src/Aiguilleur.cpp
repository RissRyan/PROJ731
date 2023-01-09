#include "Aiguilleur.h"

void Aiguilleur::listenPort()
{
	sf::SocketSelector socketSelector;
	sf::TcpListener listener;
	std::vector<sf::TcpSocket*> clients;

	// bind the listener to a port
	if (listener.listen(53000) != sf::Socket::Done)
	{
		std::cout << "Bababoey\n";
	}

	socketSelector.add(listener);

	while (true)
	{
		// Make the selector wait for data on any socket
		if (socketSelector.wait())
		{
			// Test the listener
			if (socketSelector.isReady(listener))
			{
				// The listener is ready: there is a pending connection
				sf::TcpSocket* client = new sf::TcpSocket;

				if (listener.accept(*client) == sf::Socket::Done)
				{

					socketSelector.add(*client);

					clients.push_back(client);

					std::cout << "Un nouveau client a ete ajoute : " << client << std::endl;


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

				for (auto client : clients)
				{
					if (socketSelector.isReady(*client))
					{
						this->receiveMessage(client);
					}
				}
			}
		}

	}
}
