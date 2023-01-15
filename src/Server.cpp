#include "Server.h"

void Server::addData(Data* data)
{
	m_allData.push_back(data);
}

Data* Server::getData(std::string fileName)
{
	for (auto data : m_allData)
	{
		if (data->name == fileName)
		{
			return data;
		}
	}

	return nullptr;
}

std::string Server::traitQuery(const Packet& packet)
{
	Data* data = this->getData(packet.message);

	if (data != nullptr)
	{
		return data->data;
	}
	else
	{
		return "Ce fichier n'existe pas !";
	}
}

void Server::listenPort(const int port)
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
			if (m_socketSelector.wait())
			{
				// Test the listener
				if (m_socketSelector.isReady(m_listener))
				{
					// The listener is ready: there is a pending connection
					sf::TcpSocket* aiguilleur = new sf::TcpSocket;

					if (m_listener.accept(*aiguilleur) == sf::Socket::Done)
					{

						m_socketSelector.add(*aiguilleur);

						m_aiguilleurs.push_back(aiguilleur);

						std::cout << "Un nouveau aiguilleur a ete ajoute : " << aiguilleur << std::endl;


					}
					else
					{
						// Error, we won't get a new connection, delete the socket
						std::cout << "Erreur nouvelle connexion aiguilleur" << std::endl;
						delete aiguilleur;
					}
				}
				else
				{
					// The listener socket is not ready, test all other sockets (the clients)

					for (int i = 0; i < m_aiguilleurs.size(); i++)
					{
						sf::TcpSocket* aiguilleur = m_aiguilleurs[i];

						if (m_socketSelector.isReady(*aiguilleur))
						{

							Packet resp = this->receiveMessage(aiguilleur);

							if (resp.status == sf::Socket::Status::Done)
							{
								std::cout << aiguilleur << " : " << resp.message << std::endl;

								this->sendMessage(aiguilleur, traitQuery(resp));
							}
							else
							{
								std::cout << "L'aiguilleur : " << aiguilleur << " s'est deconnecte !" << std::endl;

								m_socketSelector.remove(*aiguilleur);
								aiguilleur->disconnect();
								m_aiguilleurs.erase(m_aiguilleurs.begin() + i);
								i--;
							}

						}
					}
				}
			}
		}

	}
}

