#pragma once


#include<iostream>
#include<fstream>
#include <iomanip>
#include"cities.h"
#include"trains.h"
using namespace std;



class schedule
{
public:
	char from[20];
	char to[20];
	char strDate[12];
	char strtime[7];
	char ID[10];
	double price;

	int count_schedule();
	schedule* create_schedule();
	int& operator[](int);
	void range(char*,char*,char*,char*,char*,int );
	int addSchedule();
	int readSchedule();
	int updateSchedule();
	int deleteSchedule();
	int travel_from_to();
	schedule(char*,char*,char*,char*,char*,float);
	schedule(void);
	~schedule(void);
};

