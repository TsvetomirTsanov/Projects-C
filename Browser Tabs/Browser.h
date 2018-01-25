#ifndef BROWSER_H
#define BROWSER_H

#include <string.h>
#include<iostream>

#include "Tab.h"

using namespace std;

class Browser
{
public:
    Browser();
    Browser(const Browser&);
    Browser& operator=(const Browser&);
    ~Browser();

    void GoTo(const char*);
    void Back();
    void Forward();

    void addTab(const char*);
    void closeTab();

    Tab* getFirst();
    void print();

private:
    void clear();

private:
    Tab* first;
    Tab* current;
};

#endif // BROWSER_H
