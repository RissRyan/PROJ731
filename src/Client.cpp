#include "Client.h"



Client::Client(std::string name)
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
		std::cout << this->receiveMessage(&m_socket) << std::endl;
	}

	this->sendMessage(&m_socket, "ABCDEFGHIJ");
}
