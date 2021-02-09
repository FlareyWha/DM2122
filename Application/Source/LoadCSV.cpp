#include "LoadCSV.h"
#include <fstream>
#include <iostream>

LoadCSV::LoadCSV()
{
	for (int i = 0; i < 256; i++)
	{
		width[i] = 0;
		currLine[i] = "0";
	}
	count = 0;
}

void LoadCSV::loadCSV()
{
	std::ifstream csvFile("Source//FontData.csv");
	if (!csvFile.is_open())
	{
		std::cout << "Impossible to open. Are you in the right directory ?\n";
		exit(1);
	}

	while (!csvFile.eof())
	{
		std::getline(csvFile, currLine[count], '\n');
		width[count] = std::stoi(currLine[count]);
		count++;
	}

	csvFile.close();
}

int LoadCSV::getWidth(int i)
{
	return width[i];
}
