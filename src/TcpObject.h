#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>

// Struct Packet pour g�rer les probl�mes de d�connexion ou autre (d'o� la pr�sence un attribut status)

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
	
	sf::Socket::Status connectToRemote(const std::string& nameServer, const int port); // Permet de se connecter � une machine particuli�re

	void sendMessage(sf::TcpSocket* socket, std::string mess); // Envoie de messages par un socket particulier

	Packet receiveMessage(sf::TcpSocket* socket); // R�ception de messages per un socket particulier
};

