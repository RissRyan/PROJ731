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
	Client(std::string name);

	void receiveFromServer();
};
