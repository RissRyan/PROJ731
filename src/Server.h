#pragma once

#include <fstream>
#include <functional>

#include "ServerObject.h"

// Struct Data pour charger et mettre en forme les fichiers

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

// Classe pour les serveurs

class Server : public ServerObject
{
private:
	std::string m_name = "Serveur ";
	std::vector<Data*> m_allData;
	sf::Thread m_thread;

	std::vector<sf::TcpSocket*> m_aiguilleurs;

public:
	Server(std::string name) : m_thread(std::bind(&Server::listenPort, this, 20000)) // On met l'écoute du port 20000 sur un thread à part
	{
		m_name += name;

		std::cout << "Vous etes : " << m_name << std::endl;

		m_thread.launch();
	}

	void addData(Data* data);

	Data* getData(std::string fileName);

	std::string traitQuery(const Packet& packet);

	void listenPort(const int port);




};

