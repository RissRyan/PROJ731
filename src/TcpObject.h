#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>

// Struct Packet pour gérer les problèmes de déconnexion ou autre (d'où la présence un attribut status)

struct Packet {
	sf::Socket::Status status;
	std::string message = "";

	Packet(sf::Socket::Status stat, std::string mess)
	{
		this->status = stat;
		this->message = mess;
	}
};

// Classe """abstraite""" pour tous les objets (Utilisateurs, Aiguileurs, Serveurs)

class TcpObject
{
protected:

	sf::TcpSocket m_socket;
	sf::Mutex mutex_socket;

public:
	
	sf::Socket::Status connectToRemote(const std::string& nameServer, const int port); // Permet de se connecter à une machine particulière

	void sendMessage(sf::TcpSocket* socket, std::string mess); // Envoie de messages par un socket particulier

	Packet receiveMessage(sf::TcpSocket* socket); // Réception de messages per un socket particulier
};

