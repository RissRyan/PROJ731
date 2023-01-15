#pragma once

#include "TcpObject.h"

// Classe pour l'utilisateur

class Client : public TcpObject
{
private:
	std::string m_name = "Client ";
public:
	Client(std::string name, std::string serverName, const int port);

	void receiveFromServer(); // Thread� pour pouvoir recevoir et envoyer en m�me temps
};
