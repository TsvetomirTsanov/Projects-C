#include "Student.h"
#include <iostream>

using namespace std;

Student::Student() : name(NULL), age(0), subject(NULL), grade(0), date(NULL)
{}

Student::Student(const char* name,const  int age,const  char* subject,const  int grade,const  char* date) :
        age(age), grade(grade)
{
    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);

    this->subject = new char[strlen(subject)+1];
    strcpy(this->subject, subject);

    this->date = new char[strlen(date)+1];
    strcpy(this->date, date);
}

Student::~Student()
{
    destroy();
}

Student::Student(const Student& other)
{
    copy(other);
}

Student& Student::operator=(const Student& rhs)
{
    if (this != &rhs)
    {
        destroy();
        copy(rhs);
    }
    return *this;
}

void Student::copy(const Student& other)
{
    name = new char[strlen(other.name)+1];
    strcpy(name, other.name);

    subject = new char[strlen(other.subject)+1];
    strcpy(subject, other.subject);

    date = new char[strlen(other.date)+1];
    strcpy(date, other.date);

    age = other.age;
    grade = other.grade;
}

void Student::destroy()
{
    delete[] name;
    delete[] subject;
    delete[] date;

    name = subject = date = NULL;
    age = grade = 0;
}

void Student::print() const
{
    cout << name << "," << age << "," << subject << "," << grade << "," << date << endl;
}
