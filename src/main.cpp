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