#pragma once

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class cities
{
	char city[20];

public:
	cities(void);
	~cities(void);

	char* getCity();
	void setCity(char*);

	int cities::readCity();
	int addCity();
	int removeCity();

};

