// PROJET AIGUELLEUR XDDD AYAAA.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

 
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>


class Client
{
private:
	std::string m_name = "Client ";
	sf::TcpSocket m_socket;
public:
	Client(std::string name)
	{
		m_name += name;

		std::cout << "Vous etes : " << m_name << std::endl;
		sf::Socket::Status status = m_socket.connect("localhost", 53000);
		if (status != sf::Socket::Done)
		{
			std::cout << "N'a pas pu se co au serveur\n";
		}
		else
		{
			std::cout << "Ok\n";
		}

		char data[4] = "abc";

		m_socket.send(data, 4);
	}
};

class Aiguilleur {
private:
    std::string m_name = "Aiguilleur ";
public:
    Aiguilleur(std::string name)
    {
		m_name += name;

		std::cout << "Vous etes : " << m_name << std::endl;
    }

    void listenPort()
    {
        sf::SocketSelector socketSelector;
        sf::TcpListener listener;
		std::vector<sf::TcpSocket*> clients;

        // bind the listener to a port
        if (listener.listen(53000) != sf::Socket::Done)
        {
            std::cout << "Bababoey\n";
        }

		socketSelector.add(listener);

		while (true)
		{
			// Make the selector wait for data on any socket
			if (socketSelector.wait())
			{
				// Test the listener
				if (socketSelector.isReady(listener))
				{
					// The listener is ready: there is a pending connection
					sf::TcpSocket* client = new sf::TcpSocket;

					if (listener.accept(*client) == sf::Socket::Done)
					{

						socketSelector.add(*client);

						clients.push_back(client);

						std::cout << "Un nouveau client a ete ajoute : " << client << std::endl;


					}
					else
					{
						// Error, we won't get a new connection, delete the socket
						std::cout << "Erreur connexion" << std::endl;
						delete client;
					}
				}
				else
				{
					
					// The listener socket is not ready, test all other sockets (the clients)

					for (auto client : clients)
					{
						if (socketSelector.isReady(*client))
						{
							char data[100];
							std::size_t received;

							// TCP socket:
							if (client->receive(data, 100, received) != sf::Socket::Done)
							{
								// error...
							}
							else
							{
								std::cout << "Received " << received << " bytes : " << data << std::endl;
							}

						} 
					}
				}
			}

		}
    }

};

int main()
{
	std::string c;
	std::cout << "s/c \n";

	std::cin >> c;

	if (c == "s")
	{
		Aiguilleur ok("Wesh");

		ok.listenPort();
	}
	else
	{
		Client ok("AAAAA");
	}

	char x;

	std::cin >> x;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
