#pragma once

#include "TcpObject.h"
class ServerObject : public TcpObject
{
protected:
	sf::SocketSelector m_socketSelector;
	sf::TcpListener m_listener;
	std::vector<sf::TcpSocket*> m_clients;

public:

	virtual void listenPort(const int port) = 0;

};

