#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Student.h"

class DynamicArray
{
    public:
        DynamicArray();
        ~DynamicArray();
        DynamicArray(const DynamicArray& other);
        DynamicArray& operator=(const DynamicArray& other);

        void add(Student&);
        void print();

        Student& getAt(int);
        void setAt(int, Student&);
        int getSize();

    private:
        void copy(const DynamicArray&);
        void free();
        void reallocate();

    private:
        Student* students;
        int size;
        int allocated;
};

#endif // DYNAMICARRAY_H
