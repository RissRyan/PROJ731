#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>

#include "TcpObject.h"

class Client : public TcpObject
{
private:
	std::string m_name = "Client ";
public:
	Client(std::string name)
	{
		m_name += name;

		std::cout << "Vous etes : " << m_name << std::endl;
		sf::Socket::Status status = m_socket.connect("localhost", 53000);


		if (status != sf::Socket::Done)
		{
			std::cout << "N'a pas pu se co au serveur\n";
		}
		else
		{
			std::cout << "Vous etes connecté !\n";
		}

		this->sendMessage("ABCDEFGHIJ");
		this->sendMessage("ABCDEFGHIJ");
		this->sendMessage("ABCDEFGHIJ");
		this->sendMessage("ABCDEFGHIJ");

		this->sendMessage("ABCDEFGHIJ");
		this->sendMessage("ABCDEFGHIJ");
		this->sendMessage("ABCDEFGHIJ");
		this->sendMessage("ABCDEFGHIJ");
	}
	/*
	~Client()
	{
		m_socket.disconnect();
	}*/
};

