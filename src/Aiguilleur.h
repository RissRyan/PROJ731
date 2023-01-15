#pragma once

#include "ServerObject.h"

// Classe pour l'aiguilleur

class Aiguilleur : public ServerObject 
{
private:
	std::string m_name = "Aiguilleur ";

	std::vector<sf::TcpSocket*> m_clients; // Liste des clients
	std::vector<sf::TcpSocket*> m_servers; // Les des clients

	int iRepartiteur = 0; // int pour la r�partion de charge

public:
	Aiguilleur(std::string name);

	void addServer(std::string serverName, const int port); // Ajoute un serveur � m_servers

	void listenPort(const int port); // �coute sur un port, pour les clients.

	sf::TcpSocket* getServer(); // Permet de savoir quel serveur utiliser (r�partion de charge)

	void traitReponse(sf::TcpSocket* socket, std::string response); // Traiter la r�ponse d'un client
};

