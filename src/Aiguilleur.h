#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>

#include "TcpObject.h"

class Aiguilleur : public TcpObject 
{
private:
	std::string m_name = "Aiguilleur ";
public:
	Aiguilleur(std::string name)
	{
		m_name += name;

		std::cout << "Vous etes : " << m_name << std::endl;
	}

	void listenPort();

};

