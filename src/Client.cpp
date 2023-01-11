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
		Packet resp = this->receiveMessage(&m_socket);
		if (resp.status == sf::Socket::Status::Done)
		{
			std::cout << resp.message << std::endl;
		}
		else
		{
			std::cout << "Pb de reception !" << std::endl;
		}

	}

	this->sendMessage(&m_socket, "ABCDEFGHIJ");
}