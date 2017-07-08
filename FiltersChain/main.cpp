#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <assert.h>
#include <errno.h>

using namespace std;


#include "FilterChain.h"
#include "Filter.h"

void menu(FilterChain& s)
{
    int selection;
  for(;;){
  cout<<"\n Menu";
  cout<<"\n 1   Dobavqne na filter...";
  cout<<"\n 2 - Premahvane na filter...";
  cout<<"\n 3   Serializirane na klasa... ";
  cout<<"\n 4 - Deserializirane na klas...";
  cout<<"\n 5 - Filtrirane...";
  cout<<"\n ----------------------";
		cout<<"\n 0 - Exit";
        cout<<"\n Enter selection: (0-5)";
        cin>>selection;
        if (!cin.fail()){

   if(selection == 1){

          s.add_filter();

   }else if(selection == 2){

          s.remove_filter();

   }else if(selection == 3){

        s.serialize();

   }else if(selection == 4){

	    s.deserialize();

   }else if(selection == 5){

	   s.Print();

   }else if(selection == 0)
	   break;
    else{
       cout<<endl<<"NEVALIDEN IZBOR !!!"<<endl;
	   break;
   }

        }
  }
}
int main()
{
    //menu(a);
   FilterChain a, b;
   // a.deserialize();
    //b.deserialize();
    Filter c,d;
    c.set_word("Sd");
    d = c;

    return 0;
}
