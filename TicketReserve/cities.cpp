#include "cities.h"

cities::cities(void)
{}

cities::~cities(void)
{}

int count_cities()
{ 
	cities grad;
	fstream file;
	file.open("cities.txt", ios::in|ios::out);
	char line[256];
	int counterCity = 0;
	while(file.getline(line,256,'\n'))
		counterCity++;
	file.close();
	return counterCity;
}

cities* create_obj_cities()
{
	fstream file;
	file.open("cities.txt",ios::in);  //otvarq faila za 4etene

	if(!file)
	{ 
		cout << "Could not open the file" << endl;
		file.close();
	}	
	
	int counterCity = count_cities();
	cities* grad = new cities[counterCity];
	for (int i = 0; i < counterCity;i++)
		file.getline(grad[i].getCity(),20);

	file.close();
	return &grad[0];

}


bool check_city(char* ccity){
	fstream f;
	f.open("cities.txt",ios::in|ios::out);

	if(!f){
		cout<< "could not open the file"<<endl;
			f.close();
			return 1;
	}
	cities city;
	while (!f.eof())
	{		
		f.getline(city.getCity(),20);
		if(strcmp(city.getCity(),ccity ) == 0) 
			return true;
	}

	return false;
}

int cities::readCity(){
	cities* city = create_obj_cities();
	int counterCity = count_cities();
	cout << endl;
	for (int i = 0; i < counterCity;i++)
		cout << (i+1) << " "<< city[i].city << endl;
	cout << endl;
	delete [] city;
	return 0;
}

int cities::addCity(){            

	fstream f("cities.txt",ios::out|ios::app);
	if(!f)
	{ 
		cout<< "Could not open the file: "<< endl;
		return 0;
	}
	cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
	cout<< "Vuvedete nov grad: "<< endl;
	char newCity[20];	
	cin.getline(newCity,20);

	if(!check_city(newCity))
	{
		f << endl << newCity;
		f.close();
		return 0;
	}
	f.close();
	cout << " Tozi grad veche sushtestvuva! "<<endl; 
	return 0;
}

int cities::removeCity(){
	cities city;
	city.readCity();
	int x;
	cout << "Koi grad iskate da bude iztrit? "<<endl;
	cin >> x;
	int counterCity = count_cities();
	if(x >= 1 && x < counterCity)
	{
		cities* city = create_obj_cities();	
		ofstream NewFile("removedCity.txt",ios::out);
		if(!NewFile)
		{
			cout<<"could not open the new file"<< endl;
			NewFile.close();
		}
		for(int i = 0; i < counterCity;i++)
		{
			if((x-1) == i)
				i++;

			NewFile << city[i].city << endl;	
		}

		NewFile.close();

		//remove("cities.txt");
		//rename("removedCity.txt","cities.txt");
		return 0;

	}
	cout << "Vuveli ste greshen nomer za grad: "<< endl;
	return 1;
}


char * cities::getCity()
{
	return city;
}

void cities::setCity(char* city )
{
	strcpy(this->city, city);
}

