#pragma once

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class cities
{
public:
	char city[20];
	 

	int cities::readCity();
	int addCity();
	int removeCity();
	cities(void);
	~cities(void);
};

