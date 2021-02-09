#ifndef LOAD_CSV_H
#define LOAD_CSV_H
#include <string>

class LoadCSV
{
private:
	int width[256];
	std::string currLine[256];
	int count;

public:
	LoadCSV();
	void loadCSV();
	int getWidth(int i);
};

#endif

