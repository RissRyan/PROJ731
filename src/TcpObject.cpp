#include "TcpObject.h"


void TcpObject::sendMessage(sf::TcpSocket* socket, std::string mess)
{
	sf::Packet packet;

	packet << mess;

	//mutex_socket.lock();

	sf::Socket::Status status = socket->send(packet);

	//mutex_socket.unlock();

	if (status != sf::Socket::Done)
	{
		std::cout << "Erreur dans le send !" << std::endl;
	}
}

Packet TcpObject::receiveMessage(sf::TcpSocket* socket)
{
	sf::Packet sfmlPacket;

	std::string mess;

	// TCP socket:

	mutex_socket.lock();

	sf::Socket::Status status = socket->receive(sfmlPacket);

	mutex_socket.unlock();

	sfmlPacket >> mess;

	if (status == sf::Socket::Error)
	{
		Packet packet(status, std::string("[RECEIVE] Error\n"));
		return packet;

	}
	else if (status == sf::Socket::Disconnected)
	{
		Packet packet(status, std::string("[RECEIVE] Disconnected\n"));
		return packet;
	}
	else
	{
		Packet packet(status, std::string(mess));
		return packet;
	}
}