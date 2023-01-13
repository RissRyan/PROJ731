#pragma once

#include "ServerObject.h"

class Aiguilleur : public ServerObject 
{
private:
	std::string m_name = "Aiguilleur ";

	std::vector<sf::TcpSocket*> m_servers;
public:
	Aiguilleur(std::string name)
	{
		m_name += name;

		std::cout << "Vous etes : " << m_name << std::endl;
	}

	void addServer(std::string serverName, const int port);

	void listenPort(const int port);

	void traitReponse(sf::TcpSocket* socket, std::string response);

	std::string getData(std::string fileName);
};

