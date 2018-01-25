#ifndef TAB_H
#define TAB_H

#include <iostream>
#include <string.h>
#include <time.h>

using namespace std;

class Tab
{
public:
    Tab();
    Tab(const char*, Tab*, Tab*);
    Tab(const Tab&);
    Tab& operator=(const Tab&);
    ~Tab();

    void setNextTab( Tab*);
    void setPreviousTab( Tab*);
    void setUrl(const char*);
    void setDate();

    Tab* getNextTab();
    Tab* getPreviousTab();
    char* getUrl();
    time_t getDate();

    void print();

private:
    char* url;
    time_t date;

private:
    Tab* previous;
    Tab* next;
};

#endif // TAB_H
