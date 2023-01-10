#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>
#include <fstream>

#include "TcpObject.h"

struct Data
{
	std::string name = "";
	std::string data = "";

	Data();

	Data(std::string fileName)
	{
		this->loadData(fileName);
	}

	void loadData(std::string fileName)
	{
		std::string filePath = "./Data/" + fileName;

		std::fstream file;

		file.open(filePath);

		if (file.is_open())
		{
			this->name = fileName;

			std::string buffer((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());

			this->data = buffer;
		}
		else
		{
			std::cout << "Une erreur s'est produite lors du chargement de la donnee !" << std::endl;
		}
	}
};

class Server : public TcpObject
{
private:
	std::string m_name = "Serveur ";
	std::vector<Data*> m_allData;

public:
	Server(std::string name)
	{
		m_name += name;

		std::cout << "Vous etes : " << m_name << std::endl;
	}

	void addData(Data* data)
	{
		m_allData.push_back(data);
	}

	Data* getData(std::string fileName)
	{
		for (auto data : m_allData)
		{
			if (data->name == fileName)
			{
				return data;
			}
		}

		return nullptr;
	}
};

