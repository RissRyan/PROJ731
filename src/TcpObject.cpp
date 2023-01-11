#include "TcpObject.h"


void TcpObject::sendMessage(sf::TcpSocket* socket, std::string mess)
{
	const char* data = mess.c_str();

	int len = std::strlen(data);

	sf::Socket::Status status = socket->send(data, len + 1);

	if (status != sf::Socket::Done)
	{
		std::cout << "Erreur dans le send !" << std::endl;
	}
}

std::string TcpObject::receiveMessage(sf::TcpSocket* socket)
{

	char data[100];
	std::size_t received;

	// TCP socket:

	sf::Socket::Status status = socket->receive(data, 100, received);

	if (status == sf::Socket::Error)
	{
		socket->disconnect();
		return "[RECEIVE] Error\n";

	}
	else if (status == sf::Socket::Disconnected)
	{
		//socket->disconnect();
		return std::string("[RECEIVE] Disconnected\n");
	}
	else
	{
		std::cout << "Received " << received << " bytes : ";
		return std::string(data);
	}
}