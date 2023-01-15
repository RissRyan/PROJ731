#pragma once

#include "TcpObject.h"

// Classe abstraite pour les objets de type serveur (aiguilleurs et serveurs)

class ServerObject : public TcpObject
{
protected:
	// listener pour accepter de nouvelles connexions et socket selector pour bloquer sur un groupe de sockets
	sf::TcpListener m_listener;
	sf::SocketSelector m_socketSelector;


public:

	virtual void listenPort(const int port) = 0; // methode vituelle pure d'écoute de port

};

