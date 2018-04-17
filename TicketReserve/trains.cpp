#include "trains.h"

ostream& operator<<(ostream& out, const trains& train);
istream& operator>>(istream& in, trains& train);


int trains::count_obj_trains()
{ 
	fstream file;
	file.open("trains.txt", ios::in|ios::out);
	char line[256];
	int counterTrain = 0;
	
	while(file.getline(line,256,'\n'))
		counterTrain++;
	file.close();
	
	return counterTrain;
}

bool check_choise(int x)
{
	trains train1;
	int counterTrain = train1.count_obj_trains();
	if(x >=1 && x <= counterTrain)
		return true;

	return false;
}

trains* trains::create_obj_trains(){
	fstream file;
	file.open("trains.txt",ios::in);  //otvarq faila za 4etene

	if(!file)
	{ 
		cout << "Could not open the file" << endl;
		file.close();
	}	
	
	char ctrainID[10];
	int cseats;
	char cdescription[100];
		
	char* ptr;
	trains train1;
	int counterTrain = train1.count_obj_trains();
	trains* train = new trains[counterTrain];                     
	char line[1024];
	int i = 0;
	while(file.getline(line,1024,'\n')){

		ptr = strtok(line,", ");
		strcpy(train[i].trainID, ptr);
		
		ptr = strtok(NULL,", ");
		train[i].seats = atoi(ptr);		
		
		ptr = strtok(NULL,",");
		strcpy(train[i].description , ptr);		
		i++;
	}
	file.close();                     //zatvarq faila
	return &train[0];
}

void save_in_file(trains* train)
{	
	trains train1;
	int counterTrain = train1.count_obj_trains();
	fstream file;
	file.open("trains.txt",ios::out);

	for ( int i = 0; i < counterTrain; i++){
		file << train[i];
	}
	file.close();   
}

bool trains::check_trains(char* cID)
{
	fstream file;
	file.open("trains.txt",ios::in);  //otvarq faila za 4etene

	if(!file)
	{
		cout << "Could not open the file" << endl;
		file.close();
	}	
	char ctrainID[10];
	char* ptr;
	trains vlak;
	                     
	char line[1024];
	while(file.getline(line,1024,'\n'))
	{
		ptr = strtok(line,", ");
		strcpy(vlak.trainID, ptr);
		cout << vlak.trainID << ", ";
		if(strcmp(cID,vlak.trainID)==0) 
		{
			file.close();
			return true;
		}
	}

	file.close();
	return false;
}


//read trains function
int trains::readTrains(){
	
	trains *train = create_obj_trains();
	int counterTrain = count_obj_trains();
	cout << endl;
	for (int i = 0; i < counterTrain; i++){
		cout << (i+1) << " " << train[i].trainID << " " << train[i].seats << " " << train[i].description << endl;
	}
	cout << endl;
	delete[] train;
	return 0;
}

//add trains function
int trains::addTrain(){
	fstream file;
	file.open("trains.txt",ios::out|ios::app);    
	
	if(!file) 
		cout << "ne e otv faila"<< endl;

	cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
	cout << "vuvedete ID na noviq vlak: "<< endl;
	char newID[10];
	cin.getline(newID,10);
	if(!check_trains(newID))
	{
		cout<<"vuvedete broi na mestata: "<< endl;    
		char newSeats[100];
		cin.getline(newSeats,100);
	
		cout << "vuvedete opisanie: " << endl; 
		char newDescript[100];
		cin.getline(newDescript,100);
	
		file << endl << newID << ", " << newSeats << ", " << newDescript;   
		file.close();  
		return 0;
	}
	cout << "Tozi vlak veche sushtestvuva! "<< endl;
	return 1;
}

//update trains function
int trains::updateTrain(){
	trains::readTrains();
	cout << "Izberete koi vlak da bude promenen" << endl;
	int i;
	cin >> i;
	if (check_choise(i))
	{	
		trains train2;
		trains *train = train2.create_obj_trains();

		cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );   // za cin.getline 4isti potoka
		cout << " Vuvedete novo ID na vlaka: " << endl;
		char newID[10];
		cin.getline(newID,10);
		strcpy(train[i-1].trainID,newID);	

		cout << " Vuvedete broi mesta: " << endl;
		char newSeats[100];
		cin.getline(newSeats,100);
		train[i-1].seats = atoi(newSeats);

		cout << "Vuvedete kratko opisanie: "<< endl;
		char newDescr[100];
		cin.getline(newDescr,100);
		strcpy(train[i-1].description,newDescr);

		save_in_file(train); 
		delete [] train;
	}
	cout << "Vuveli ste greshen nomer! "<< endl; 
	return 0;
}

//deleteTrain function
int trains::deleteTrain()
{
	trains::readTrains();
	fstream newfile;
	newfile.open("newTrains.txt",ios::out);

	if(!newfile){
		cout<< "could not open the newfile" << endl; 
		newfile.close();
	}else{cout << "file open" << endl;}

	cout << "Izberete koi vlak da bude iztrit" << endl;
	int x;
	cin >> x;
	if (check_choise(x))
	{	
		trains *vlak = create_obj_trains(); 
		int counterTrain = count_obj_trains();
		for(int i = 0; i < counterTrain; i++)
		{
			if((x-1) == i) 
				i++;
			newfile << vlak[i];
		}

		newfile.close();
		delete [] vlak;

		//remove("trains.txt");
		//rename("newTrains.txt","trains.txt");
	}else {cout << "Vuveli ste gre6en nomer!" << endl; } 
	return 0;
}


trains& trains::operator=(trains const & rhs){
	if(this != &rhs){
		strcpy(this->trainID,rhs.trainID);
		this->seats = rhs.seats;
		strcpy(this->description,rhs.description);
	}
	return *this;
}
ostream& operator<<(ostream& out, const trains& train)
{
	out << train.trainID << " " << train.seats << " " << train.description<< endl;
	return out;
}
istream& operator>>(istream& in, trains& train)
{ 
	in.getline(train.trainID, 10, ',');
	in >> train.seats;
	in.getline(train.description, 100, '\n');
	return in;
}
trains::trains(char newTrainID[],int newSeats, char newDescript[]){
	strcpy(trainID,newTrainID);
	seats = newSeats;
	strcpy(description,newDescript);
	
} 
trains::trains()
{
}
trains::~trains()
{
}


