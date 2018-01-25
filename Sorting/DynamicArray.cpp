#include "DynamicArray.h"

DynamicArray::DynamicArray() : size(0), allocated(0), students(NULL)
{}

DynamicArray::~DynamicArray()
{
    free();
}

DynamicArray::DynamicArray(const DynamicArray& other)
{
    copy(other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& rhs)
{
    if (this != &rhs)
    {
        free();
        copy(rhs);
    }
    return *this;
}

void DynamicArray::free()
{
    delete[] students;
    students = NULL;
    allocated = size = 0;
}

void DynamicArray::copy(const DynamicArray& other)
{
    students = new Student[other.allocated];

    for(int i = 0; i < other.allocated; i++)
        students[i] = other.students[i];

    allocated = other.allocated;
    size = other.size;
}

void DynamicArray::reallocate()
{
    allocated = (allocated == 0 ? 2 : allocated*2);
    Student* temp = new Student[allocated];

    for(int i = 0; i < size; i++)
        temp[i] = students[i];

    delete[] students;
    students = temp;
}

void DynamicArray::add(Student& student)
{
    if(size >= allocated)
        reallocate();

    students[size++] = student;
}

int DynamicArray::getSize()
{
    return size;
}

Student& DynamicArray::getAt(int n)
{
    return students[n];
}

void DynamicArray::setAt(int n, Student& student)
{
    students[n] = student;
}

void DynamicArray::print()
{
    for(int i = 0 ; i < size; i++)
        students[i].print();
}
