#include "schedule.h"


ostream& operator<<(ostream& out, const schedule& sch);


int schedule::count_schedule()
{ 
	schedule razpis;
	fstream file;
	file.open("schedule.txt", ios::in);
	if(!file){
		cout<< "couldn't open file!"<<endl;
		file.close();
	}
	char line[256];
	int counterSchedule = 0;
	while(file.getline(line,256,'\n'))
		counterSchedule++;
	file.close();
	return counterSchedule;
}

schedule* schedule::create_schedule()
{
	int counterSchedule = count_schedule();
	fstream file;
	file.open("schedule.txt", ios::in);
	char* ptr;
	schedule *razpis = new schedule[counterSchedule]; 
	char line[1024];
	int i = 0;
	while(file.getline(line,1024,'\n')){
		ptr = strtok(line,"-> ");
		strcpy(razpis[i].from, ptr);

		ptr = strtok(NULL,"->, ");
		strcpy(razpis[i].to, ptr);	

		ptr = strtok(NULL,", ");
		strcpy(razpis[i].strDate, ptr);

		ptr = strtok(NULL,", ");
		strcpy(razpis[i].strtime, ptr);

		ptr = strtok(NULL,", ");
		strcpy(razpis[i].ID, ptr);

		ptr = strtok(NULL,", ");
		razpis[i].price = atof(ptr);	
		
		i++;
	}
	file.close(); 
	return &razpis[0];
}

void save_in_file_schedule(schedule* sched)
{	
	schedule razpis1;
	int counterSchedule = razpis1.count_schedule();
	fstream file;
	file.open("schedule.txt",ios::out); //otvarq faila za pisane v nego
	
	for ( int i = 0; i < counterSchedule; i++){
		file << sched[i];
	}
	file.close();   //zatvarq faila
}

bool check_choise_sch(int x)
{
	schedule razpis1;
	int counterSchedule = razpis1.count_schedule();
	if(x >=1 && x <= counterSchedule)
		return true;
	return false;
}


int schedule::readSchedule()
{
		schedule *razpis = create_schedule(); 
		schedule razpis1;
		int counterSchedule = razpis1.count_schedule();
		for (int i = 0; i < counterSchedule; i++)
		{
			cout << (i+1) << " " << razpis[i];
		}
		cout << endl;

		delete [] razpis; 
		return 0;
}

int schedule::addSchedule()
{	

	fstream file;
	file.open("schedule.txt",ios::out|ios::app);  
	if(!file) cout << "Couldn't open the file!"<< endl;

	cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

	cout << "Vuvedete nachalen grad: "<< endl;
	char cfrom[20];
	cin.getline(cfrom,20);
	
	cout<<"Vuvedete kraen grad: "<< endl;    ///da stane int
	char cto[20];
	cin.getline(cto,20);
	
	cout << "Vuvedete data,kato q razdelite s . : " << endl;   // trqbva da se razdeli na 4asti
	char cstrDate[12];
	cin.getline(cstrDate,12);                           // proverka za datata
	
	cout << "Vuvedete 4as na otputuvane: " << endl;   //trqbva da se razdeli na 4asti
	char cstrtime[7];
	cin.getline(cstrtime,7);  

	cout << "Vuvedete ID na vlaka: "<< endl;
	char ctrainID[10];
	cin.getline(ctrainID,10);

	cout << "Vuvedete cena na bileta: "<< endl;  // proverka dali ne e -
	float cprice;
	cin >> cprice;

	file  << cfrom << "->" << cto << ", " << cstrDate << ", " << cstrtime << ", "<< ctrainID << ", " << cprice << endl;   // zapisva vuv faila
	file.close();                    //zatvarqme faila

	return 0;
}

int schedule::updateSchedule()
{
	schedule::readSchedule();

	cout << "Izberete koe razpisanie da bude promeneno:" << endl;
	int i;
	cin >> i;
	if (check_choise_sch(i))
	{	schedule razpis1;
	
		schedule *razpis = razpis1.create_schedule();           

		cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' ); 
		
		cout << " Vuvedete nachalen grad: " << endl;
		char cfrom[20];
		cin.getline(cfrom,20);
		strcpy(razpis[i-1].from,cfrom);
	
		cout << " Vuvedete kraen grad: " << endl;
		char cto[20];
		cin.getline(cto,20);
		strcpy(razpis[i-1].to,cto);

		cout << " Vuvedete data: " << endl;    // proverka za pravilno vuvejdane na data
		char cstrdate[12];
		cin.getline(cstrdate,12);
		strcpy(razpis[i-1].strDate,cstrdate);

		cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
		cout << " Vuvedete chas: " << endl;
		char cstrtime[7];
		cin.getline(cstrtime,7);
		strcpy(razpis[i-1].strtime,cstrtime);

		cout << " Vuvedete ID na vlaka: " << endl;
		char cID[10];
		cin.getline(cID,10);
		strcpy(razpis[i-1].ID,cID);
	
		cout << " Vuvedete cena na bileta: " << endl;  // proverka dali e vuveden ?
		char cprice[10];
		cin.getline(cprice,10);
		razpis[i-1].price = atof(cprice);	
			
		save_in_file_schedule(razpis); 

		delete [] razpis;
	}else{cout << "Vuveli ste greshen nomer: "<< endl;}
	return 0;
}

int schedule::deleteSchedule()
{
	schedule::readSchedule();
	fstream newfile;
	newfile.open("newSchedule.txt",ios::out);
	if(!newfile){
		cout<< "could not open the newfile" << endl; 
		newfile.close();
	}

	cout << "Izberete koe razpisanie da bude iztrito:" << endl;
	int x;
	cin >> x;
	if (check_choise_sch(x))
	{	schedule razpis1;
	
		schedule *razpis = razpis1.create_schedule(); 
		int counterSchedule = (razpis1.count_schedule()-1);
		for(int i = 0; i < counterSchedule; i++){
			if((x-1) == i) 
				i++;
			newfile << razpis[i];
		}
		newfile.close();
		delete [] razpis;
		//remove("schedule.txt");
		//rename("newSchedule.txt","schedule.txt");
	}else{ cout<<"Vuveli ste gre6en nomer! "<<endl;}

	return 0;
}

int schedule::travel_from_to()
{
	schedule::readSchedule();
	cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

	cout << "Vuvedete nachalen grad: "<<endl;
	char cfrom[20];
	cin.getline(cfrom,20);

	cout << "Vuvedete kraen grad: "<< endl;
	char cto[20];
	cin.getline(cto,20);

	schedule razpis1;
	int counterSchedule = razpis1.count_schedule();
	schedule *razpis = razpis1.create_schedule();
	
	for (int i = 0; i < counterSchedule; i++)
	{
		if ( (strcmp(razpis[i].from,cfrom) == 0) &&  (strcmp(razpis[i].to,cto) == 0))
			{
				cout << razpis[i];
			} 		
	}
	delete [] razpis;
	return 1;
}


ostream& operator<<(ostream& out, const schedule& sch)
{
	out << sch.from<< "->" << sch.to <<  ", " << sch.strDate <<  ", " << sch.strtime <<  ", " << sch.ID <<  ", " << sch.price << endl;
	return out;
}
int& schedule::operator[] (int x)
{
 return x;
}
schedule::schedule(char* cfrom,char* cto,char* cstrdate,char* cstrtime,char* ctrainID,float cprice) //////////////////////////////////////////////////
{
	strcpy(from,cfrom);
	strcpy(to,cto);
	strcpy(strDate,cstrdate);
	strcpy(strtime,cstrtime);
	strcpy(ID,ctrainID);
	price = cprice;

}
schedule::schedule(void)
{
}
schedule::~schedule(void)
{
}

