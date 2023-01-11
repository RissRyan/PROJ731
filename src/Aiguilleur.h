#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <SFML/Network.hpp>

#include "Server.h"

class Aiguilleur : public TcpObject 
{
private:
	std::string m_name = "Aiguilleur ";
	std::vector<Server*> m_servers;
	sf::SocketSelector m_socketSelector;
	sf::TcpListener m_listener;
	std::vector<sf::TcpSocket*> m_clients;
public:
	Aiguilleur(std::string name)
	{
		m_name += name;

		std::cout << "Vous etes : " << m_name << std::endl;
	}

	void addServer(Server* server);

	void listenPort();

	void traiterReponse(std::string response);


};

