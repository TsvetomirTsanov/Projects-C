#include <iostream>
#include "Tab.h"
#include "Browser.h"
#include "MergeSort.h"

using namespace std;

void interface()
{
    Browser browser;
    char command[10];
    char argument[128];
    while(true)
    {
        cin >> command;

        if(strcmp(command, "GO") == 0)
        {
            cin>>argument;
            browser.GoTo(argument);
        }
        else if(strcmp(command, "INSERT") == 0)
        {
            cin>>argument;
            browser.addTab(argument);
        }
        else if(strcmp(command, "BACK") == 0)
        {
            browser.Back();
        }
        else if(strcmp(command, "FORWARD") == 0)
        {
            browser.Forward();
        }
        else if(strcmp(command, "REMOVE") == 0)
        {
            browser.closeTab();
        }
        else if(strcmp(command, "PRINT") == 0)
        {
            browser.print();
        }
        else if(strcmp(command, "PRINT2") == 0)
        {
            browser.print2();
        }
        else if(strcmp(command, "SORT") == 0)
        {
            cin>>argument;
            MergeSort(browser.getFirst(), argument);
        }
    }
}

int main()
{
    interface();
    return 0;
}
