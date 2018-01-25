#include "Tab.h"

Tab::Tab() : next(NULL), previous(NULL)
{
    url = new char[12];
    strcpy(url, "about:blank");

    date = time(0);
}

Tab::Tab(const char* url = "about:blank", Tab* prevTab = NULL, Tab* nextTab = NULL)
{
    setNextTab(nextTab);
    setPreviousTab(prevTab);

    this->url = new char[strlen(url) +1];
    strcpy(this->url, url);

    date = time(0);
}

Tab::Tab(const Tab& other)
{
    url = new char[strlen(other.url)];
    strcpy(url,other.url);
    next = other.next;
    previous = other.previous;
    date = other.date;
}

Tab& Tab::operator=(const Tab& other)
{
    if(this != &other)
    {
        delete[] url;
        url = new char[strlen(other.url)];
        strcpy(url,other.url);

        date = other.date;
    }
    return *this;
}

Tab::~Tab()
{
    delete[] url;
}

void Tab::setUrl(const char* url)
{
    delete[] this->url;
    this->url = new char[strlen(url) + 1];
    strcpy(this->url, url);
}

void Tab::setDate()
{
    date = time(0);
}

void Tab::setNextTab(Tab* tab)
{
    this->next = tab;
    if(tab != NULL)
        tab->previous = this;

}

void Tab::setPreviousTab(Tab* tab)
{
    this->previous = tab;
    if(tab != NULL)
        tab->next = this;
}

Tab* Tab::getNextTab()
{
    return next;
}

Tab* Tab::getPreviousTab()
{
    return previous;
}

char* Tab::getUrl()
{
    return url;
}

time_t Tab::getDate()
{
    return date;
}

void Tab::print()
{
    cout<< url << " " << date << endl;
}
