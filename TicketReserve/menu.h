#pragma once

#include<iostream>
#include"cities.h"
#include"trains.h"
#include"schedule.h"

using namespace std;

struct command
	{	
		int  key;
		const char* name;
		void print_menu();
		int enter_choice();
		int execute_command(int);
	}
	commands[] = {
		{1, "Izvejdane na gradovete "},
		{2, "Dobavqne na grad "},
		{3, "Iztrivane na grad "},
		{4, "Izvejdane na vlakovete "},
		{5, "Dobavqne na vlak "},
		{6, "Redaktirane na vlak "},
		{7, "Iztrivane na vlak "},
		{8, "Izvejdane na razpisanieto "},
		{9, "Dobavqne na razpisanie "},
		{10, "redaktirane na razpisanieto "},
		{11, "Iztrivane na razpisanie "},
		{12, "Putuvane ot do "},
		{13, "Izhod"},
		{0, NULL}
		
	};
	
