#include "TcpObject.h"


sf::Socket::Status TcpObject::connectToRemote(const std::string& nameServer, const int port)
{
	return this->m_socket.connect(nameServer, port);
}


void TcpObject::sendMessage(sf::TcpSocket* socket, std::string mess)
{
	sf::Packet sfmlPacket; // Paquet de la SFML pour �viter certains probl�mes (fin de cha�nes de caract�res et comminucation entre diff�rents OS)

	sfmlPacket << mess;

	//mutex_socket.lock();

	sf::Socket::Status status = socket->send(sfmlPacket);

	//mutex_socket.unlock();

	if (status != sf::Socket::Done)
	{
		std::cout << "Erreur dans l'envoie a " << socket  << std::endl;
	}
}

Packet TcpObject::receiveMessage(sf::TcpSocket* socket)
{
	sf::Packet sfmlPacket; // Paquet de la SFML pour �viter certains probl�mes (fin de cha�nes de caract�res et comminucation entre diff�rents OS)

	mutex_socket.lock();

	sf::Socket::Status status = socket->receive(sfmlPacket);

	mutex_socket.unlock();


	std::string mess;

	sfmlPacket >> mess; // On �crit le message re�u dans le string mess

	// On g�re les diff�rentes erreurs

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