#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <SFML/Network.hpp>

#include "Client.h"
#include "Aiguilleur.h"

int main()
{
	
	std::string c;
	std::cout << "s/c \n";

	std::getline(std::cin, c);

	if (c == "s")
	{
		Server server("serveur"); // PORT 20000

		// On crée un fichier à charger dans le server

		Data* myData = new Data("Test.txt");

		server.addData(myData);

		// Aiguilleur

		Aiguilleur aig("Aig");

		aig.addServer("localhost", 20000);

		aig.listenPort(42000);

		delete myData;
	}
	else
	{
		Client ok("AAAAA", "localhost", 42000);
	}

	/*
	Aiguilleur ok("Ok");
	Aiguilleur whatsup("Hmmm");	
	sf::Thread thread1(std::bind(&Aiguilleur::listenPort, &ok, 42000));
	sf::Thread thread2(std::bind(&Aiguilleur::listenPort, &whatsup, 30000));

	thread1.launch();
	thread2.launch();

	if (whatsup.connectToRemote("localhost", 42000))
	{
		std::cout << "N'a pas pu se co à Ok\n";
	}
	else
	{
		
		std::cout << "Less go Ok" << std::endl;
	}

	if (ok.connectToRemote("localhost", 30000))
	{
		std::cout << "N'a pas pu se co à Whatsup\n";
	}
	else
	{

		std::cout << "Less go Whatsup" << std::endl;
	}

	thread1.wait();
	thread2.wait();*/

}