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

FilterChain::FilterChain()
{
    std::cout << " -> [" << this << "] "
              << "Entering DynamicArray()\n";

    fillters = NULL;
    allocated_memory = 0;
    number = 0;
}


///
/// Конструктор за копиране (copy constructor)
///
FilterChain::FilterChain(FilterChain const & other)
{
    std::cout<< " -> [" << this << "] "
             << "Entering DynamicArray(DynamicArray const &)\n";
    CopyFrom(other);
}



///
/// Оператор за присвояване (assignment operator)
///
FilterChain& FilterChain::operator=(FilterChain const & other)
{
    if(this != &other)
    {
        Free();
        CopyFrom(other);
    }
    return *this;
}

bool FilterChain::operator==(FilterChain & other)
{
    bool flag1 = false;
    int count = -1;
    if(this->number != other.number)
        return false;
    else{
        for(int i = 0; this->number; i ++){
            for(int j = 0; j < this->number; j++)
                {
                    if(!strcmp(this->fillters[i]->get_word(), other.fillters[j]->get_word()))
                        flag1 = true;
                }
            ++count;
            if(!flag1)
            {
                return false;
            }
            else
                flag1 = false;
            if(count == this->number - 1)
                return true;
        }
    }
}
bool FilterChain::operator!=(FilterChain const & other)
{
    bool flag1 = false;
    int count = -1;
    if(this->number != other.number)
        return true;
    else{
        for(int i = 0; this->number; i ++){
            for(int j = 0; j < this->number; j++)
                {
                    if(!strcmp(this->fillters[i]->get_word(), other.fillters[j]->get_word()))
                        flag1 = true;
                }
            ++count;
            if(!flag1)
            {
                return true;
            }
            else
                flag1 = false;
            if(count == this->number - 1)
                return false;
        }
    }
}
FilterChain& FilterChain::operator+=(Filter other)
{
    this->add_filter(other.get_word());
}

FilterChain& FilterChain::operator|(Filter& other)
{
    this->add_filter(other.get_word());
    return *this;
}
FilterChain& FilterChain::operator+(FilterChain& other)
{
    FilterChain newFilter;
    bool flag1 = false;
    for(int i = 0; i < this->number; i++){
        newFilter.add_filter(this->fillters[i]->get_word());
        cout<< i << endl;
    }
    for(int i = 0; i < other.number; i++){
        for(int j = 0; j < this->number; j++)
            {
                if(!strcmp(other.fillters[i]->get_word(), this->fillters[j]->get_word()))
                    flag1 = true;
            }

        if(!flag1)
        {
            cout<<"ERROR";
            newFilter.add_filter(other.fillters[i]->get_word());
        }
        else
            flag1 = false;
    }
    return newFilter;
}
FilterChain& FilterChain::operator-=(char* sent)
{
    FilterChain temp;
    int count = 0;
    for(int i = 0; i < this->number; i++)
        if(fillters[i]->filter(sent))
            temp.add_filter(fillters[i]->get_word());
    Free();
    CopyFrom(temp);
    return *this;
}

Filter* FilterChain::operator[](int a)
{
    if(a > this->number)
        cout<<"Out of boundries"<<endl;
    else
        return fillters[a];
}
Filter* FilterChain::operator[](char* sent)
{
    bool flag = true;
    for(int i = 0; i < this->number && flag; i++)
        if(!fillters[i]->filter(sent)){
                return fillters[i];
            flag = false;
            break;
        }
    if(!flag)
        cout<<"Ne systestvuva takyv filter." << endl;
}

///
/// Деструктор
///
FilterChain::~FilterChain()
{
    std::cout<< " -> [" << this << "] "
             << "Entering ~DynamicArray()\n";
    Free();
}


/// Копира данните от масива other в текущия обект
void FilterChain::CopyFrom(FilterChain const & other)
{
    fillters = new Filter*[other.allocated_memory];

    for(size_t i = 0; i < other.allocated_memory; i++)
        fillters[i] = other.fillters[i];

    allocated_memory = other.allocated_memory;
    number = other.number;
}


///
/// Освобождава паметта заета от динамичния масив
///
void FilterChain::Free()
{
    delete [] fillters;
    fillters = NULL;
    number = 0;
    allocated_memory = 0;
}

/// Преоразмерява динамичния масив, така че той да съдържа
/// NewSize елемента.
void FilterChain::Reallocate(int NewSize)
{
    std::cout<< " -> [" << this << "] "
             << "Reallocating " << allocated_memory << " -> " << NewSize << "\n";

    Filter** pTemp = new Filter*[NewSize];

    // колко елемента ще бъдат копирани
    size_t limit = std::min(allocated_memory, NewSize);

    for(size_t i = 0; i < limit; i++)
        pTemp[i] = fillters[i];

    delete [] fillters;

    fillters = pTemp;
    allocated_memory = NewSize;
}


/// Добавя нов елемент в динамичния масив
///
/// Новият елемент се добавя в края на масива.
///
void FilterChain::add_filter()
{
    if(number >= allocated_memory)
    {
        size_t NewSize = (allocated_memory == 0 ? 2 : allocated_memory*2);

        Reallocate(NewSize);
    }
    cout<<".................."<<endl;
    Filter* another = new Filter;

    char* word = new char[30];
    cout<< "Insert filter word: ";
    cin.sync();
    cin>>word;
    another->set_word(word);
    fillters[number++] = another;//heree
}


void FilterChain::add_filter(char* word )
{
    if(number >= allocated_memory)
    {
        size_t NewSize = (allocated_memory == 0 ? 2 : allocated_memory*2);

        Reallocate(NewSize);
    }
    cout<<".................."<<endl;
    Filter* another = new Filter;
    char* word1 = new char[30];

    //strcpy(word1,word);
    another->set_word(word);
    //another->set_word(word1);
    fillters[number++] = another;
}


///premahva posledniq filter
void FilterChain::remove_filter()
{
    if(number){
        cout<<"Deleting the filter world: " << fillters[number] << endl;
        delete fillters[number--];
    }
}

/// funkciq koqto pozvolqva vyvezdane na text ot konzolata
/// i go izvezda ako premine uspe6no vsi4ki filtri
void FilterChain::Print() const
{
    std::cout<<endl<< "Dynamic Array at 0x" << this
             << ", buffer at 0x" << fillters
             << ", size (" << number
             << " / " << allocated_memory << ")\n";
    //char *s = new char[256];

    char text[256];


    while(!cin.eof())
    {
        cout<<"Vyvdete text: ";
        cin.sync();
        cin.getline(text,256);

        cout<< endl << "Nizyt "<< text << " ste byde proveren za nali4ie na dumite ";
        for(int j = 0; j < number; j++)
            cout <<fillters[j]->get_word() << ", ";
        cout<< endl;

        bool flag = true;
        int i = 0;
        while(flag && i < number)
        {
            flag = fillters[i]->filter(text);
            if(flag)
                cout<<"true";
            else cout<<"false";
            i++;
            //s = fillters[i]->get_filtered();
            //cout<< i << " filter " << s << endl;
        }
        cout<<endl;
        if(flag)
            cout<< text << endl;
        else
            cout<<text << " sydyrza nqkoq ot dumite." << endl;
    }
}



void FilterChain::serialize()
{
    char file_name[22];
    cout<<"Ime na faila? ";
    cin>>file_name;
    ofstream out(file_name, ios::binary);
    out.write((char*)&number, sizeof(number));
    for(int i = 0; i < number; i++)
        fillters[i]->serialize(out);
    out.close();
}


void FilterChain::deserialize()
{
    Free();
    int len, total;
    cout<<"Enter file name: ";
    char file_name[22];
    cin >> file_name;
    ifstream in(file_name);
    char* word = new char[30];
    in.read((char*)&total, sizeof(int));
    for(int i = 0; i < total; i++)
    {
        in.read((char*)&len, sizeof(int));
        in.read(word, len);
        add_filter(word);
    }
    in.close();
}

