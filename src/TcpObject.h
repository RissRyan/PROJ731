#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>

struct Packet {
	sf::Socket::Status status;
	std::string message = "";

	Packet(sf::Socket::Status stat, std::string mess)
	{
		this->status = stat;
		this->message = mess;
	}
};


class TcpObject
{
protected:

	sf::TcpSocket m_socket;
	sf::Mutex mutex_socket;

public:

	void sendMessage(sf::TcpSocket* socket, std::string mess);

	Packet receiveMessage(sf::TcpSocket* socket);
};

