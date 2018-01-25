#include "Browser.h"

Browser::Browser()
{
    current = first = new Tab();
}

Browser::Browser(const Browser& other)
{
    ///
}

Browser& Browser::operator=(const Browser& other)
{
    if(this != &other)
    {
       ///
    }
    return *this;
}
Browser::~Browser()
{
    clear();
}

void Browser::GoTo(const char* url)
{
    current->setUrl(url);
    current->setDate();
}

void Browser::addTab(const char* url)
{
    current = new Tab(url, current, current->getNextTab());
}

void Browser::Forward()
{
    if(current->getNextTab() != NULL)
        current = current->getNextTab();
}

void Browser::Back()
{
    if(current->getPreviousTab() != NULL)
        current = current->getPreviousTab();
}

void Browser::closeTab()
{
    bool isTherePrevTab = current->getPreviousTab();
    bool isThereNextTab = current->getNextTab();

    Tab* temp = current;
    if(isThereNextTab)
    {
        if(isTherePrevTab)
        {
            current->getPreviousTab()->setNextTab(current->getNextTab());
            current->getNextTab()->setPreviousTab(current->getPreviousTab());
        }
        else /// FIRST ELEMENT TO BE DELETED
        {
            current->getNextTab()->setPreviousTab(NULL);
            first = first->getNextTab();
        }
        current = current->getNextTab();
    }
    else
    {
        if(isTherePrevTab)
        {
            current->getPreviousTab()->setNextTab(NULL);
            current = current->getPreviousTab();
        }
        else  /// ONLY ONE TAB
        {
            first = current = new Tab();
        }
    }

    delete temp;
}
Tab* Browser::getFirst()
{
    return first;
}

void Browser::print()
{
    Tab* temp = first;
    while(temp)
    {
        if(temp == current)
            cout<< "> ";
        temp->print();
        temp = temp->getNextTab();
    }
}

void Browser::clear()
{
	Tab* pCurrent = first;
	Tab* pOld = first;
	while(pCurrent)
    {
        pOld = pCurrent;
		pCurrent = pCurrent->getNextTab();
		delete pOld;
	}

	first = NULL;
	current = NULL;
}
