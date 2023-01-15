#pragma once

#include <fstream>
#include <functional>

#include "ServerObject.h"

struct Data
{
	std::string name = "";
	std::string data = "";

	Data();

	Data(std::string fileName)
	{
		this->loadData(fileName);
	}

	void loadData(std::string fileName)
	{
		std::string filePath = "./Data/" + fileName;

		std::fstream file;

		file.open(filePath);

		if (file.is_open())
		{
			this->name = fileName;

			std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

			this->data = buffer;
		}
		else
		{
			std::cout << "Une erreur s'est produite lors du chargement de la donnee !" << std::endl;
		}
	}
};

class Server : public ServerObject
{
private:
	std::string m_name = "Machine ";
	std::vector<Data*> m_allData;
	sf::Thread m_thread;

	std::vector<sf::TcpSocket*> m_aiguilleurs;

public:
	Server(std::string name) : m_thread(std::bind(&Server::listenPort, this, 20000))
	{
		m_name += name;

		std::cout << "Vous etes : " << m_name << std::endl;

		m_thread.launch();
	}

	Data* getData(std::string fileName)
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


	std::string traitQuery(const Packet& packet)
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

	void listenPort(const int port)
	{
		// bind the listener to a port
		if (m_listener.listen(port) != sf::Socket::Done)
		{
			std::cout << "Bababoey\n";
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
							std::cout << "Erreur connexion" << std::endl;
							delete aiguilleur;
						}
					}
					else
					{
						// The listener socket is not ready, test all other sockets (the clients)

						for (int i = 0; i < m_aiguilleurs.size(); i++)
						{
							sf::TcpSocket* aiguilleur = m_aiguilleurs[i];
							//std::cout << client << std::endl;

							if (m_socketSelector.isReady(*aiguilleur))
							{

								Packet resp = this->receiveMessage(aiguilleur);

								if (resp.status == sf::Socket::Status::Done)
								{
									std::cout << aiguilleur->getRemoteAddress() << " : " << resp.message << std::endl;

									this->sendMessage(aiguilleur, traitQuery(resp));
								}
								else
								{
									std::cout << "L'aiguilleur : " << aiguilleur << " s'est déconnecté !" << std::endl;

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

	void addData(Data* data)
	{
		m_allData.push_back(data);
	}
};

