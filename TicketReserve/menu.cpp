#include "menu.h"


void command::print_menu()
{	cout << "\t\t MENU\n";
	for(int i = 0;commands[i].name; i++)
		cout << commands[i].key << " : " <<commands[i].name << endl;
}

int command::enter_choice()
{	cout<< "Izberete deistvie: "<<endl;
	int x;
	cin >> x;
	if(x >= 1 && x <= 13) return x;
	cout << "Nepoznata comanda! "<< endl;
	return -1; 
}

int command::execute_command(int x)
{
	cities grad;
	trains vlak;
	schedule razpis;
	switch(x)
	{

	case 1: 
		grad.readCity();
		break; 
	case 2:
		grad.addCity();
		break;
	case 3: grad.removeCity();
		break;
	case 4: vlak.readTrains();
		break;
	case 5: vlak.addTrain();
		break;
	case 6: vlak.updateTrain();
		break;
	case 7: vlak.deleteTrain();
		break;
	case 8: razpis.readSchedule();
		break;
	case 9: razpis.addSchedule();
		break;
	case 10: razpis.updateSchedule();
		break;
	case 11: razpis.deleteSchedule();
		break;
	case 12: razpis.travel_from_to();
		break;
	case 13:  return 1;
		break;

	}
	
	return 0;
}



int main()
{

	int komanda,result = 0;
	command com;
	do{
		cout << endl;
	com.print_menu();
	komanda = com.enter_choice();
	if(komanda < 0) continue;
	result = com.execute_command(komanda);

	}while(result == 0); 
	return 0;
}
