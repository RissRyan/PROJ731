#include "TcpObject.h"


void TcpObject::sendMessage(std::string mess)
{
	const char* data = mess.c_str();

	int len = std::strlen(data);

	sf::Socket::Status status = m_socket.send(data, len + 1);

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
		std::cout << "[RECIEVE] Error : client disconnected" <<  std::endl;
		socket->disconnect();
	}
	else if (status == sf::Socket::Disconnected)
	{
		return std::string("L!!");
	}
	else
	{
		std::cout << "Received " << received << " bytes : " << data << std::endl;
	}

	return std::string(data);
}