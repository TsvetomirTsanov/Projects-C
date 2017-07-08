#include <iostream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

bool isLeap(int year, int month)
{
    return ((!(year%4) && (year%100) || !(year%400)));
}
bool monthOK(int month, int year)
{
    return (month >= 1 && month <= 12 && year > 2000 && year < 2050);
}
bool dayOK (int dd, int mm, int year)
{
    if(mm == 2 && dd <= 29 && isLeap(year, mm))
        return true;
    if(mm == 2 && dd <= 28 && isLeap(year, mm))
        return true;
    if((mm==1||mm==3||mm==5||mm==7||mm==8||mm==10||mm==12)&&(dd<=31))
        return true;
    if((mm==4||mm==6||mm==9||mm==11)&&dd<=30)
        return true;
}
bool isDateOK(string b)
{
    int size = b.length();
    char a[size];
    strcpy(a, b.c_str());
    int j = 0, count = 0;
    int length = strlen(a);
    bool Check1 = 1;
    for(int i = 0; i < length; i ++)
    {
        if(!((a[i] >= '0' && a[i] <= '9') || a[i] == '.' || a[i] == ','))
            Check1 = 0;
    }
    char day[3], month[3], year[5];
    for(int i = 0; i < length; i++)
    {
        if((a[i] != '.' && a[i] != ',') && count == 0){
            day[j] = a[i];
            j++;
        }else if((a[i] != '.' && a[i] != ',') && count == 1){
            month[j] = a[i];
            j++;
        }else if((a[i] != '.' && a[i] != ',') && count == 2){
            year[j] = a[i];
            j++;
        }else{
            j = 0;
            count++;
        }
    }
    int d = atoi(day); int m = atoi(month); int y = atoi(year);
    cout<<d << "   " << m << "   "<< y;
    return Check1 && monthOK(m,y) && dayOK(d,m,y);
}

class AdressBook
{
public:
AdressBook();

void addNewBook();
void updateBook();
void updateBook2();
void updateBook3();

void simpleSearch();
void otherSearch();

void Doklad();
void print();
void print2(int);
//print all
void printAll();

void serializeNumbers(ofstream&);
void serializeNumbers(ifstream&, int);
void serializeRest(ofstream&, char[], char[][20], char[][20], char[][20], string);

void deserializeNumbers();
void deserializeNumbers( int);
void deserializeRest();

private:
    int number;
    int mobileNo;
    int homeNo;
    int mailNo;
    int BdateNo;

};
AdressBook::AdressBook()
{
    ifstream s("number");
    s >> number;
    s.close();
}
void AdressBook::print()
{
    cout<<"number: " << number << " mobileNo: " << mobileNo << " homeNo: " << homeNo << " mailNo: " << mailNo << "bdateNO: " << BdateNo << endl;
}

//print all
void AdressBook::printAll()
{
    ifstream readRest("rest");
    string line;
    for(int i = 0; i < number;i++){
        getline(readRest, line, '\n');
        cout<<line<<endl;
    }
    readRest.close();
}
//print one address book
void AdressBook::print2(int n)
{
    ifstream readNumbers("numbers");
    ifstream readRest("rest");
    string line;
    deserializeNumbers(n);
    readNumbers.close();
    for(int i = 0; i < number; i++)
    {
        if(i != n)
            getline(readRest, line, '\n');
        else
        {
            getline(readRest, line, ',');
            cout<<"Ime: " << line << endl;
            for(int i = 0; i < mobileNo; i++){
                getline(readRest, line, ',');
                cout<<"Mobilen Nomer " << i+1 << ": "<< line <<endl;
            }for(int i = 0; i < homeNo; i++){
                getline(readRest, line, ',');
                cout<<"Home Nomer " << i+1 << ": "<< line <<endl;
            }for(int i = 0; i < mailNo; i++){
                getline(readRest, line, ',');
                cout<<"Email Nomer " << i+1 << ": "<< line <<endl;
            }
            if(BdateNo != 0){
                getline(readRest, line, '\n');
                cout<<"Bdate: " << line << endl;
            }
        }
    }
    cout<<"--------------------"<<endl;

    readRest.close();
}

void AdressBook::addNewBook()
{
    ofstream writeNumbers("numbers", ios::app | ios::out);
    ofstream writeRest("rest", ios::app | ios::out);
    number+=1;
    int count = 0;
    string date;
    char name[50];
    char telephoneM[11][20],  telephoneH[11][20], emails[10][20];
    cout<<"Name: ";
    cin.ignore();
    cin.getline(name, 50, '\n');
    char yn;
    cout<<"Add Mobilen nomer? Y/N";
    cin>>yn;
    if(yn == 'Y' || yn == 'y'){
        cout<<"enter the number... ";
        cin>>telephoneM[count];
        count++;
        char yn2;
        cout<<"Add another mobile number? Y/N";
        cin>>yn;
        while(yn != 'n' && yn != 'N')
        {
            cout<<"enter the new number...";
            cin>>telephoneM[count];
            count++;
            cout<<"Add another mobile number? Y/N";
            cin>>yn;
        }
    }
    else mobileNo = 0;
    mobileNo = count;
    count = 0;

    cout<<"Add home nomer? Y/N";
    cin>>yn;
    if(yn == 'Y' || yn == 'y'){
        cout<<"enter the number... ";
        cin>>telephoneH[count];
        count++;
        cout<<"Add another home number? Y/N";
        cin>>yn;
        while(yn != 'n' && yn != 'N')
        {
            cout<<"enter the new number...";
            cin>>telephoneH[count];
            count++;
            cout<<"Add another mobile number? Y/N";
            cin>>yn;
        }
    }
    else homeNo = 0;
    homeNo = count;
    count = 0;

    cout<<"Add email? Y/N";
    cin>>yn;
    if(yn == 'Y' || yn == 'y'){
        cout<<"enter the email... ";
        cin>>emails[count];
        count++;
        cout<<"Add another email? Y/N";
        cin>>yn;
        while(yn != 'n' && yn != 'N')
        {
            cout<<"enter the new email...";
            cin>>emails[count];
            count++;
            cout<<"Add another mobile number? Y/N";
            cin>>yn;
        }
    }else mailNo = 0;
    mailNo = count;

    cout<<"Add birthday date ? Y/N";
    cin>>yn;
    if(yn == 'Y' || yn == 'y'){
        cout<<"enter the date... ";
        cin>>date;
        while(!isDateOK(date))
        {
            cout<<"enter the date...";
            cin>>date;
        }
        BdateNo = 1;
    }else BdateNo = 0;
    ofstream out("number");
    out<<number;
    out.close();
    serializeNumbers(writeNumbers);
    serializeRest(writeRest,name, telephoneM, telephoneH, emails, date);
    writeNumbers.close();
    writeRest.close();
}

//write one line
void AdressBook::serializeNumbers(ofstream& file)
{
   // ofstream file("numbers");
    file << mobileNo << ' ' << homeNo << ' ' << mailNo << ' ' << BdateNo << endl;
    //file.close();
}

void AdressBook::serializeNumbers(ifstream& file,int n)
{
    string line;
    ofstream newfile("newnumbers");
    for(int i = 1; i <= number; i++){
        getline(file, line, '\n');
        if(i != n)
            newfile << line << endl;
        else
            newfile << mobileNo << ' ' << homeNo << ' ' << mailNo << ' ' << BdateNo << endl;
    }
    newfile.close();
}

//write one line
void AdressBook::serializeRest(ofstream& file, char name[], char mobile[][20], char home[][20], char emails[][20], string date)
{
    file << name << ',';
    if(mobileNo != 0)
        for(int i = 0; i < mobileNo; i++)
            file<<mobile[i]<< ',';
    if(homeNo !=0 )
        for(int i = 0; i < homeNo; i++)
            file<<home[i]<< ',';
    if(mailNo != 0)
        for(int i = 0; i < mailNo; i++)
            file<<emails[i]<< ',';
    if(BdateNo !=0 )
        file << date << endl;
}
//read one line
void AdressBook::deserializeNumbers()
{
    ifstream file("numbers");
    file >> mobileNo >> homeNo >> mailNo >> BdateNo;
    file.close();
}
//read one line by number
void AdressBook::deserializeNumbers(int n)
{
    ifstream readNumbers("numbers");
    for(int i = 1; i <= number; i++){
        readNumbers >> mobileNo >> homeNo >> mailNo >> BdateNo;
        if( i == n)
            break;
    }
    readNumbers.close();
}
//read one line
void AdressBook::deserializeRest()
{
    ifstream file("rest");
    string name, date, useless;
    //preska4a redove dokato ne nameri pravilniq
    for(int i = 0; i < number; i++)
        getline(file, useless, '\n');
    char telephoneM[mobileNo][20],  telephoneH[homeNo][20], emails[mailNo][20];
    getline(file, name,',');
    cout<< name <<endl;;
    for(int i = 0; i < mobileNo; i++){
        file.getline(telephoneH[i], 15, ',');
        cout<<telephoneH[i] << endl;
    }
    for(int i = 0; i < homeNo; i++){
        file.getline(telephoneM[i], 15,',');
        cout<<telephoneM[i] << endl;
    }
    for(int i = 0; i < mailNo; i++){
        file.getline(emails[i], 15, ',');
        cout<<emails[i] << endl;
    }
    getline(file,date, '\n');
    cout<<date << endl;
    file.close();
}

//iztriva pole
void AdressBook::updateBook()
{
    ifstream readRest("rest");
   // ifstream readNumbers("numbers");
    ofstream out("newfile");
    int numBook, num;
    cout<<"Book No? ";
    cin>>numBook;
    deserializeNumbers(numBook);
    //readNumbers.close();
    int all = mobileNo + homeNo + mailNo + BdateNo ;
    string name, date, useless;

    //zapisva redovete koito nqma da se promenqt
    for(int i = 1; i < number+1; i++){
        if(i != numBook){
            getline(readRest, useless, '\n');
            out << useless << endl;
        }
        else
        {
            cout<<"Koe pole iskate da iztriete ? 2-"<< all;
            cin>>num;
            for(int i = 0; i <= all; i++)
                if(i != num)
                {
                    if(i != all)
                    {
                        getline(readRest,name, ',');
                        if(num == all && i == all-1)
                            out<<name<<endl;
                        else
                            out<<name<<',';
                    }
                    else
                    {
                        getline(readRest,name, '\n');
                        out<<name<<'\n';
                    }
                }
                else
                {
                    if(i != all)
                        getline(readRest,useless, ',');
                    else
                        getline(readRest,useless, '\n');
                }
        }
    }
    out.close();
    //remove("rest");
    //rename("newfile","rest");

     // ako e mezdu otdelnite cifri 1 -- 2<>1<>1<>1 - nqkolko if-a
     // int mobileNo;homeNo; mailNo;BdateNo;
    if(num >1 && num <= mobileNo)
        mobileNo--;
    else if(num >  mobileNo && num <= mobileNo + homeNo)
        homeNo--;
    else if(num >  mobileNo + homeNo && num <=  mobileNo + homeNo + mailNo)
        mailNo--;
    else if(num >mobileNo + homeNo + mailNo)
        BdateNo--;
    ifstream readNumbers2("numbers");
    serializeNumbers(readNumbers2,numBook);
//    readNumbers.close();
    readRest.close();

}
//promenq pole
void AdressBook::updateBook2()
{
    ifstream readRest("rest");
    ofstream out("newfile");
    int numBook, num;
    char NewName[50];
    cout<<"Book No? ";
    cin>>numBook;
    for(int i = 0; i < number; i++)
    {
        deserializeNumbers();
        if(i == num-1)
            break;
    }
    int all = mobileNo + homeNo + mailNo + BdateNo + 1;
    string name, newname, useless;
    //zapisva redovete koito nqma da se promenqt
    for(int i = 1; i < number+1; i++){
        if(i != numBook){
            getline(readRest, useless, '\n');
            out << useless << endl;
        }
        else
        {
            cout<<"Koe pole iskate da promenite ? 1-"<<all;
            cin>>num;
            if(num == 1){
                cin.ignore();
                cin.getline(NewName, 50, '\n');
            }else{
                cout<<"Vyvedete novoto ime: ";
                cin>>newname;
            }
            if(BdateNo == 1 && num == all){
                while(!isDateOK(newname))
                {
                    cout<<"enter new date...";
                    cin>>newname;
                }
            }
            for(int i = 1; i <= all; i++)
                if(i != num){
                    if(i != all){
                        getline(readRest,name, ',');
                        out<<name<<',';
                    }else{
                        getline(readRest, name, '\n');
                        out<<name<<'\n';
                    }
                }else{
                    if(i != all){
                        getline(readRest,useless, ',');
                        if(num == 1)
                            out<<NewName<<',';
                        else
                            out<<newname<<',';
                    }else{
                        getline(readRest, useless, '\n');
                        out<<newname<<endl;
                    }

                }
        }
    }
    out.close();
    readRest.close();
}
//dobavq pole
void AdressBook::updateBook3()
{
    ifstream readRest("rest");
   // ifstream readNumbers("numbers");
    ofstream out("newfile");
    int numBook, num;
    cout<<"Book No? ";
    cin>>numBook;
    deserializeNumbers(numBook);
    int all = mobileNo + homeNo + mailNo + BdateNo ;
    string name, newname, date, useless;
    //zapisva redovete koito nqma da se promenqt
    for(int i = 1; i < number+1; i++){
        if(i != numBook){
            getline(readRest, useless, '\n');
            out << useless << endl;
        }
        else
        {
            cout<<"Kakvo pole iskate da dobavite ? \n 1.mobile number  2.home number 3. email address 4.bdate";
            cin>>num;
            cout<<"Vyvedete imeto za novoto pole: ";
            cin>>newname;
            if(num == 4){
                while(!isDateOK(newname))
                {
                    cout<<"enter new date...";
                    cin>>newname;
                }
            }
            for(int i = 1; i <= all; i++){
                if(i != all)
                    getline(readRest,name, ',');
                else
                    getline(readRest,name, '\n');
                out<<name<<',';
                if(num == 1 && i == mobileNo){
                    out<<newname<<',';
                    mobileNo++;
                }else if(num == 2 && i == mobileNo + homeNo){
                    out<<newname<<',';
                    mobileNo++;
                }else if(num == 3 && i == mobileNo + homeNo + mailNo){
                    out<<newname<<',';
                    mailNo++;
                }else if(num == 4 && i == all){
                    out<<newname<<endl;
                    BdateNo++;
                }

            }
        }
    }
    ifstream readNumbers2("numbers");
     serializeNumbers(readNumbers2,numBook);
    readNumbers2.close();
    readRest.close();
}

void AdressBook::simpleSearch()
{
    ifstream readRest("rest");
    char word[40];
    cout<<"Kakvo ste tyrsite?";
    cin>>word;
    string line;
    for(int i = 0; i < number; i++)
    {
        getline(readRest, line, '\n');
        int size = line.length();
        char line2[size];
        strcpy(line2, line.c_str());
        if(strstr(line2, word)){
            print2(i);
        }
    }
  //  readNumbers.close();
    readRest.close();
}

void AdressBook::otherSearch()
{
    ifstream readRest("rest");
   // ifstream readNumbers("numbers");
    char word[40];int num;
    cout<<"Choose number of field ? \n 1.Name 2.Mobile Number 3. Home Number 4. Email 5. Bdate: ";
    cin>>num;
    cout<<" Searching for? ";
    cin>>word;
    string line, useless;
    int start, end;
    for(int i = 1; i <= number; i++){
        deserializeNumbers(i);
        int all = mobileNo + homeNo + mailNo + BdateNo + 1;
        if(num == 1){
            start = 1;
             end = 1;
        }
        else if(num == 2){
            start = 2;
            end = 1+mobileNo;
        }else if(num == 3){
            start = 2+mobileNo;
            end = 1+mobileNo+homeNo;
        }else if(num == 4){
            start = 2+mobileNo+homeNo;
            end = 1+mobileNo+homeNo+mailNo;
        }else if(num == 5){
            start = 2+mobileNo+homeNo+mailNo;
            end = all;
        }
        bool flag = true;
        //check one book for word
        for(int j = 1; j <= all; j++){
            if(j != all)
                getline(readRest, line, ',');
            else
                getline(readRest, line, '\n');
            cout<<line<<endl;
            if(j>=start && j <= end){
                int size = line.length();
                char line2[size+1];
                strcpy(line2, line.c_str());
                //cout<<line2<<endl;
                if(strstr(line2, word) && flag){
                    flag = false;
                    print2(i);

                }
            }
        }
    }
   // readNumbers.close();
    readRest.close();
}
void AdressBook::Doklad()
{
    ifstream readRest("rest");
    char temp[40];
    char array[number][40];
    string useless;
    for(int i = 0; i < number; i++)
    {
        readRest.getline(array[i], 40, ',');
        getline(readRest, useless, '\n');
    }
    for(int i = 0; i < number; i ++)
        for(int j = 0; j < number-1; j++)
        {
            if(strcmp(array[j], array[j+1]) > 0){
                strcpy(temp,array[j]);
                strcpy(array[j],array[j+1]);
                strcpy(array[j+1],temp);
        }
    ofstream out("Doklad1");
    for(int i = 0; i <number; i++)
        out<<array[i]<< endl;;
        }
}/*
void sort(char a[][30], int count)
{
    int numbers[count];
    for(int k = 0; k < count; k++)
    {
        int length = strlen(a[k]);
        bool Check1 = 1;
        int j = 0;
        for(int i = 0; i < length; i ++)
        {
            if(!((a[k][i] >= '0' && a[k][i] <= '9') || a[k][i] == '.' || a[k][i] == ','))
                Check1 = 0;
        }
        char day[3], month[3], year[5];
        for(int i = 0; i < length; i++)
        {
            if((a[k][i] != '.' && a[k][i] != ',') && count == 0){
                day[j] =a[k][i];
                j++;
            }else if((a[k][i] != '.' && a[k][i] != ',') && count == 1){
                month[j] = a[k][i];
                j++;
            }else if((a[k][i] != '.' && a[k][i] != ',') && count == 2){
                year[j] = a[k][i];
                j++;
            }else{
                j = 0;
                count++;
            }
        }
    int d = atoi(day); int m = atoi(month); int y = atoi(year);
    numbers[k] = y*10000 + m*100 + d;
    }
    ofstream out("dokladddd");
    for(int i = 0; i < count; i++ )
        out << numbers[i] << endl;

}
void AdressBook::Doklad1()
{
    char date[number][30];
   ifstream readRest("rest");
   int count = 0, counter=0;
   for(int i = 1; i <= number; i++)
   {
       deserializeNumbers(i);
       string useless;
       int all = homeNo + mobileNo + mailNo + BdateNo;
       for(int i = 0; i < all; i++)
            getline(readRest, useless, ',');
        if(BdateNo != 0){
            readRest.getline(date[count], 30, '\n');
            counter++;
        }
   }
   sort(date, counter);
}*/
int main()
{
    AdressBook a;

    int selection;
  for(;;){
  cout<<"\n Menu";
  cout<<"\n 1   Add new book";
  cout<<"\n 2   Delete field";
  cout<<"\n 3 - Change field";
  cout<<"\n 4 - Add field";
  cout<<"\n ----------------------";
  cout<<"\n 5 - SIMPLE SEARCH";
  cout<<"\n 6 - OTHER SEARCH";
  cout<<"\n 7 - Doklad";

		cout<<"\n 0 - Exit";
        cout<<"\n Enter selection: (0-9)";
        cin>>selection;
        if (!cin.fail()){

   if(selection == 1){

          cout<<"\n Adding new book..."<<endl;
		  a.addNewBook();

   }else if(selection == 2){

          cout<<"\n Deleting pole... "<<endl;
          a.updateBook();

   }else if(selection == 3){

        cout<<"\n changing pole... "<<endl;
        a.updateBook2();

   }else if(selection == 4){

	   cout<<" adding pole... "<<endl;
	   a.updateBook3();

   }else if(selection == 5){

	   cout<<" searching... ";
	   a.simpleSearch();

   }else if(selection == 6){

	   cout<<'\n'<<"searching...";
	   a.otherSearch();

   }else if(selection ==7){

	   cout<<endl<<"DOKLAD...";
       a.Doklad();

   }else if(selection > 8 || selection < 0){

    cout<<"\nNEVALIDEN IZBOR!!!"<<endl;

   }else if(selection == 0)
	   break;
   else{
       cout<<endl<<"NEVALIDEN IZBOR !!!"<<endl;
	   break;
   }
        }
  }
    return 0;
}
