#include "File.h"

File::File() : name(NULL), path(NULL), size(0)
{}

File::File(const char* name, const char* path, int size) : size(size)
{
    copy(name,path);
}
File::~File()
{
    free();
}

File::File(const File& other)
{
    copy(other);
}

File& File::operator=(const File& rhs)
{
    if (this != &rhs)
    {
        free();
        copy(rhs);
    }
   return *this;
}


void File::copy(const File& other)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    path = new char[strlen(other.path) + 1];
    strcpy(path, other.path);

    size = other.size;
}
void File::copy(const char* name, const char* path)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->path = new char[strlen(path) + 1];
    strcpy(this->path, path);
}
void File::free()
{
    delete[] name;
    delete[] path;
    size = 0;
    name = path = NULL;
}

char* File::getPath() const
{
    return path;
}

char* File::getName() const
{
    return name;
}
int File::getSize() const
{
    return size;
}
void File::print() const
{
    std::cout << name << "  " << size << std::endl;
}
