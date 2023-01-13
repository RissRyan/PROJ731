#pragma once

#include "TcpObject.h"

class Client : public TcpObject
{
private:
	std::string m_name = "Client ";
public:
	Client(std::string name, std::string serverName, const int port);

	void receiveFromServer();
};
