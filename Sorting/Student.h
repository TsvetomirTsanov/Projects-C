#ifndef STUDENT_H
#define STUDENT_H

#include <string.h>

using namespace std;
class Student
{
    public:
        Student();
        Student(const char*, const int,const char*,const int,const char*);
        Student(const Student& other);
        ~Student();
        Student& operator=(const Student& other);

        int getAge() const {return age;}
        char* getName() const {return name;}
        int getGrade() const {return grade;}
        char* getSubject() const {return subject;}
        char* getDate() const {return date;}

        bool compareNames(const Student& rhs) const
        {return strcmp(this->name, rhs.getName()) > 0;}

        bool compareAges(const int n) const
        {return age > n;}

        bool compareSubjects(const Student& rhs) const
        {return strcmp(subject, rhs.getSubject()) > 0;}

        bool compareGrades(const Student& rhs) const
        {return grade < rhs.getGrade();}

        bool compareDate(const Student& rhs) const
        {return strcmp(date, rhs.getDate()) > 0;}

        void print() const;

    private:
        void copy(const Student& other);
        void destroy();

    private:
        char* name;
        int age;
        char* subject;
        short grade;
        char* date;
};

#endif // STUDENT_H
