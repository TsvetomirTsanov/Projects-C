    #pragma once

#include "Filter.h"

class FilterChain
{
public:

    FilterChain();
    FilterChain(const FilterChain &);
    FilterChain & operator=(const FilterChain &);
    bool operator==( FilterChain &); // - сравнява само филтрите, но не и подредбата (равни FilterChain-ове дават еднакъв резултат при еднакъв вход)
    bool operator!=(const FilterChain &); //- обратното на == (различни FilterChain-ове дават различен резултат при различен вход)
    FilterChain & operator+=(Filter);// - добавя Filter към класа
    FilterChain & operator|(Filter&);  //- ляв аргумент FilterChain, десен - Filter - връща FilterChain с добавен десния аргумент
    FilterChain & operator+(FilterChain&); //  - два аргумента FilterChain - връща нов, с филтрите от аргументите без повторение
    FilterChain & operator-=(char*); // - десен аргумент char*, премахва всички филтри който филтрират подадения низ
    Filter* operator[](int);// - десен аргумент int връща филтър на позиция подаденото число
    Filter* operator[](char*);// - десен аргумент char* връща филтър филтриращ подадения низ
    ~FilterChain();

    // add filter from console to the back of the chain
    void add_filter();
    // add filter from file
    void add_filter(char* );

    // remove last added filter
    void remove_filter();

    //read/write
    void serialize();
    void deserialize();

    void Reallocate(int);
    void Free();
    void CopyFrom(FilterChain const &);
    void Print() const;
private:

    Filter** fillters;
    //broi izpolzvani kletki ot zadelenata pamet
    int number;
    //zadelena pamet
    int allocated_memory;
};

