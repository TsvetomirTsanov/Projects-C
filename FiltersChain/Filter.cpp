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

#include "Filter.h";


///constructor
Filter::Filter()
{
    word = new char[222];
    if(!word)
        cerr << "word........." << strerror(errno)<< endl;
   
	filtered = new char[222];
    if(!filtered)
        cerr << " filtered ....... " << strerror(errno)<<endl;
}

///copy constructor
Filter::Filter(const Filter& other)
{
    word = new char[strlen(other.get_word()) + 1];
    filtered = new char[strlen(other.get_filtered()) + 1];
    strcpy(word, other.word);
    strcpy(word, other.word);
}

///destructor
Filter::~Filter()
{
    delete[] word;
    delete[] filtered;
}


///operator za prisvoqvane
Filter& Filter::operator=(const Filter& other)
{
    if(this != &other){
        delete[] word;
        word = new char[strlen(other.get_word()) + 1];
        delete[] filtered;
        filtered = new char[strlen(other.get_filtered()) + 1];
        strcpy(word, other.word);
        strcpy(word, other.word);
    }
    return *this;
}

bool Filter::operator==(const Filter& other)
{
    if(!strcmp(filtered, other.filtered))
        return true;
    else
        return false;
}

bool Filter::operator!=(const Filter& other)
{
    if(strcmp(filtered, other.filtered))
        return true;
    else
        return false;

}

ostream &operator<<(ofstream &output, const Filter &other)
{
    other.serialize(output);
    return output;
}

istream &operator>>(ifstream  &input, Filter &other)
{
    other.deserialize(input);
    return input;
}


Filter& Filter::operator+=(char word2)
{
    int length = strlen(word);
    word[length++] = word2;
    return *this;
}

Filter& Filter::operator+=(char* word2)
{
    char* word1 = new char[strlen(word) + strlen(word2)+1];
    word1 = strcat(word1, word);
    strcat(word1, word2);
    word = word1;
    return *this;
}
void Filter::set_word(char*  _word)
{
    word = new char[strlen(_word)];
    //word = _word;
    strcpy(word, _word);
}

void Filter::set_filtered(char* _word)
{
    filtered = new char[strlen(filtered)];
    //filtered = _word;
    strcpy(filtered, _word);
}

///vrysta false ako word se sydyrza v sent
bool Filter::filter(char* sent)
{
    //int j = 0;
    //int count = 0;

    if(strstr(sent, word)){
        filtered = sent;
        return false;
    }else
        return true;
    else
    {
        char* temp = new(nothrow) char[strlen(sent) - strlen(word)];
            if(!temp)
                cerr << "temp........." << strerror(errno)<<endl;;
        for(int i = 0; i < strlen(sent); i++){
            if(sent[i] != word[j] && j == 0){
                temp[count] = sent[i];
                count++;
            }
            else if(sent[i] != word[j] && j > 0)
            {
                for(int c = 0; c < j; c++)
                {
                    temp[count] = word[c];
                    count++;
                }
                j = 0;
            }
            else if(sent[i] == word[j])
            {
                j++;
                if(j == strlen(word))
                    j = 0;
            }
        }
           set_filtered(temp);
           // delete[] temp;
    }
}

///zapisva dylzinata na dumata i samata duma v fail
void Filter::serialize(ofstream & file) const
{
    int len = strlen(word);
    file.write((char*)&len, sizeof(len));
    file.write(word, len);
    cout<<"Serialirizing word: " << word << " with length " << len << endl;
}
void Filter::deserialize(ifstream & file)
{
    int len, total;
    file.read((char*)&total, sizeof(int));
    file.read((char*)&len, sizeof(int));
    char* word = new char[len+1];
    file.read(word, len);
}

char* Filter::get_filtered() const
{
    return filtered;
}
char* Filter::get_word() const
{
    return word;
}


