#pragma once

#include<iostream>
#include<fstream>

using namespace std;


class trains
{
public:
	//char line[1024];
	char trainID[10];
	int seats;
	char description[100];


	trains(char[], int, char[]);
	trains(void);
	~trains();
	trains& operator=(trains const&);

	trains* create_obj_trains();
	int count_obj_trains();
	bool check_trains(char*);

	int readTrains();
	int addTrain();
	int updateTrain();
	int deleteTrain();
};


