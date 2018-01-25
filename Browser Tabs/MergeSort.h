#ifndef INTERFACE_H
#define INTERFACE_H

#include "Browser.h"

Tab* Split(Tab* my_tab)
{
    Tab* secondTab;

    if (my_tab == NULL)
        return NULL;
    else if (my_tab->getNextTab() == NULL)
        return NULL;
    else
    {
        secondTab = my_tab->getNextTab();
        //my_tab->getNextTab() = secondTab->getNextTab();
        my_tab->setNextTab(secondTab->getNextTab());
        secondTab->setNextTab(Split(secondTab->getNextTab()));
        return secondTab;
    }
}
Tab* Merge(Tab* firstTab, Tab* secondTab, char* arg)
{

    if (firstTab == NULL)
        return secondTab;
    else if (secondTab == NULL)
        return firstTab;
    else if (strcmp(arg, "TIME") == 0 && firstTab->getDate() <= secondTab->getDate())
    {
        firstTab->setNextTab(Merge(firstTab->getNextTab(), secondTab, arg));
        return firstTab;
    }
    else if (strcmp(arg, "URL") == 0 && (strcmp(firstTab->getUrl(), secondTab->getUrl()) > 0))
    {
        firstTab->setNextTab(Merge(firstTab->getNextTab(), secondTab, arg));
        return firstTab;
    }
    else
    {
        secondTab->setNextTab(Merge(firstTab, secondTab->getNextTab(), arg));
        return secondTab;
    }
}

Tab* MergeSort(Tab* my_tab, char* arg)
{
    Tab *secondTab;

    if(my_tab == NULL)
        return NULL;
    else if(my_tab->getNextTab() == NULL)
        return my_tab;
    else
    {
        secondTab = Split(my_tab);
        return Merge(MergeSort(my_tab, arg),MergeSort(secondTab, arg), arg);
    }
}




#endif // INTERFACE_H
