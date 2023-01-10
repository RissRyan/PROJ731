#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>

#include "Client.h"
#include "Aiguilleur.h"

int main()
{
	
	std::string c;
	std::cout << "s/c \n";

	std::cin >> c;

	if (c == "s")
	{
		Server server("serveur");

		// On crée un fichier à charger dans le server

		Data* myData = new Data("Test.txt");

		server.addData(myData);

		// Aiguilleur

		Aiguilleur ok("Wesh");

		ok.addServer(&server);

		ok.listenPort();

		delete myData;
	}
	else
	{
		Client ok("AAAAA");

		char x;

		std::cin >> x;
	}


}