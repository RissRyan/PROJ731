#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>


class TcpObject
{
protected:

	sf::TcpSocket m_socket;

public:

	void sendMessage(std::string mess);

	std::string receiveMessage(sf::TcpSocket* socket);
};

