#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <SFML/Network.hpp>

#include "src/Client.h"
#include "src/Aiguilleur.h"
#include "src/Server.h"

int main()
{
	std::string c;
	std::cout << "s/a/c \n"; // Choisir entre Aiguilleur, serveur, utilisateur ou test aiguilleur/aiguilleur

	std::getline(std::cin, c);


	if (c == "a") // Aiguilleur
	{
		

		Aiguilleur aig("1");

		// On se connecte au port 20000 (port du serveur)

		aig.addServer("localhost", 20000);

		// On écoute sur le port 42000 (pour les clients)

		aig.listenPort(42000);


	}
	else if(c == "s") // Serveur
	{
		Server server("1"); // PORT 20000

		// On crée un fichier à charger dans le server

		Data* myData = new Data("Test.txt");

		server.addData(myData);

	}
	else if(c == "c") // Client
	{
		Client ok("1", "localhost", 42000);
	}
	else // Test  aiguilleur/aiguilleur
	{
		// On crée 2 aiguilleurs

		Aiguilleur aig1("1");
		Aiguilleur aig2("2");

		// On les fait écouter sur des ports différents (on est en localhost)

		sf::Thread thread1(std::bind(&Aiguilleur::listenPort, &aig1, 42000));
		sf::Thread thread2(std::bind(&Aiguilleur::listenPort, &aig2, 30000));

		thread1.launch();
		thread2.launch();

		if (aig2.connectToRemote("localhost", 42000))
		{
			std::cout << "N'a pas pu se connecter à aig1\n";
		}
		else
		{

			std::cout << "Ca marche" << std::endl;
		}

		if (aig1.connectToRemote("localhost", 30000))
		{
			std::cout << "N'a pas pu se connecter à aig2\n";
		}
		else
		{

			std::cout << "Ca marche" << std::endl;
		}

		thread1.wait();
		thread2.wait();
	}
}