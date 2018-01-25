#ifndef HELPERS_H
#define HELPERS_H

#include "DynamicArray.h"

int caseChooser(const char* column)
{
    if(strcmp(column, "name") == 0)
        return 1;
    else if(strcmp(column, "subject") == 0)
        return 1;
    else if(strcmp(column, "grade") == 0)
        return 2;
    else if(strcmp(column, "date") == 0)
        return 1;
    else if(strcmp(column, "age") == 0)
        return 3;
    else
        return 4;
}
bool compare(const Student& one, const Student& two, const char* column, const char* order)
{
    bool asc = !(strcmp(order, "asc") == 0);
    bool desc = !(strcmp(order, "desc") == 0);

    bool result;

    if(strcmp(column, "name") == 0)
        result = one.compareNames(two);
    else if(strcmp(column, "subject") == 0)
        result = one.compareSubjects(two);
    else if(strcmp(column, "grade") == 0)
        result = one.compareGrades(two);
    else if(strcmp(column, "date") == 0)
        result = one.compareDate(two);
    else if(strcmp(column, "age") == 0)
        cout<<"";
    else
    {
        cout<<"Incorrect column name! "<< endl;
        return -1;
    }

    if(asc)
        return result;
    else if(desc)
        return !result;
    else
        cout << "Incorrect input";
}

void InsertionSort(DynamicArray& input, const char* column, const char* order)
{
    int n = input.getSize();

    for(int i = 1; i < n; i++)
    {
        Student temp = input.getAt(i);
        int hole = i;

        while(hole > 0 && compare(input.getAt(hole-1), temp, column, order))
        {
            input.setAt(hole, input.getAt(hole-1));
            hole -= 1;
        }
        input.setAt(hole, temp);
    }
}

void RadixSort(DynamicArray& input, const char* column, const char* order)
{
    bool asc = (strcmp(order, "asc") == 0);
    bool desc = (strcmp(order, "desc") == 0);
    int n = input.getSize();
    Student maxStudent = input.getAt(0);

    for (int i = 1; i < n; i++)
    {
        if(compare(maxStudent, input.getAt(i), column, order))
            maxStudent = input.getAt(i);
    }

    int exp = 1;

    while(maxStudent.getAge() / exp > 0)
    {
        DynamicArray decimals[10];
        for(int i = 0; i<n; i++)
        {
            int to_place = input.getAt(i).getAge() / exp %10;
            decimals[to_place].add(input.getAt(i));
        }

        int to_pos = 0;

        if(desc)
        {
            for(int i = 9; i >= 0; i--)
            {
                int count = decimals[i].getSize();
                for(int j = 0; j < count; j++)
                    input.setAt(to_pos++, decimals[i].getAt(j));
            }
        }
        else if(asc)
        {
            for(int i = 0; i<10; i++)
            {
                int count = decimals[i].getSize();
                for(int j = 0; j < count; j++)
                    input.setAt(to_pos++, decimals[i].getAt(j));
            }
        }
        exp*=10;
    }
}

void Merge(DynamicArray& left, DynamicArray& right, DynamicArray& students, const char* column, const char* order)
{
    int sizeL = left.getSize();
    int sizeR = right.getSize();
    int i = 0, j = 0, k = 0;

    while(i < sizeL && j < sizeR)
    {
        if(compare(left.getAt(i), right.getAt(j), column, order))
        {
            students.setAt(k, left.getAt(i));
            i++;
        }
        else
        {
            students.setAt(k, right.getAt(j));
            j++;
        }
        k++;
    }

    while(i<sizeL)
    {
        students.setAt(k, left.getAt(i));
        k++; i++;
    }

    while(j<sizeR)
    {
        students.setAt(k, right.getAt(j));
        k++; j++;
    }
}


void MergeSort(DynamicArray& students, const char* column, const char* order)
{
    int n = students.getSize();

    if(n<2)
        return;

    int mid = n/2;
    DynamicArray left;
    DynamicArray right;

    for(int i=0; i<mid; i++)
        left.add(students.getAt(i));

    for(int i=mid; i<n;i++)
        right.add(students.getAt(i));

    MergeSort(left, column, order);
    MergeSort(right, column, order);
    Merge(left, right, students, column, order);
}

#endif // HELPERS_H
