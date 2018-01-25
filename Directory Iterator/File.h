#ifndef File_H
#define File_H

#include <iostream>
#include <string.h>

class File
{
public:
        File();
        File(const char*, const char*, int);
        ~File();
        File(const File& other);
        File& operator=(const File& other);

        void print() const;
        char* getPath() const;
        char* getName() const;
        int getSize() const;
private:
    void copy(const File&);
    void copy(const char*, const char*);
    void free();

private:
    char* name;
    char* path;
    int size;
};

#endif // File_H
