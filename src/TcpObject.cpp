#include "TcpObject.h"


void TcpObject::sendMessage(std::string mess)
{
	const char* data = mess.c_str();

	int len = std::strlen(data);

	m_socket.send(data, len + 1);
}

std::string TcpObject::receiveMessage(sf::TcpSocket* socket)
{

	char data[100];
	std::size_t received;

	// TCP socket:
	if (socket->receive(data, 100, received) != sf::Socket::Done)
	{
		// error...
	}
	else if (socket->receive(data, 100, received) == sf::Socket::Disconnected)
	{
		return std::string("Le client est déconnecte !!!");
	}
	else
	{
		std::cout << "Received " << received << " bytes : " << data << std::endl;
	}

	return std::string(data);
}