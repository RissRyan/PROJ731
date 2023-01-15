#include "Client.h"

void Client::receiveFromServer()
{
	while (true)
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
}

Client::Client(std::string name, std::string serverName, const int port)
{
	m_name += name;

	std::cout << "Vous etes : " << m_name << std::endl;
	sf::Socket::Status status = this->connectToRemote(serverName, port); // On se connecte à l'aiguilleur


	if (status != sf::Socket::Done)
	{
		std::cout << "N'a pas pu se connecte à l'aiguilleur !\n";
	}
	else
	{
		std::string response;

		sf::Thread thread(&Client::receiveFromServer, this); // On met la reception dans un autre thread

		thread.launch();

		// Boucle d'envoie jusqu'à on tape "stop"

		do {

			std::getline(std::cin, response);

			this->sendMessage(&m_socket, response);

		} while (response != "stop");

		thread.terminate();
	}
}