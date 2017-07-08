#pragma once

class Filter
{
public:

Filter();
Filter(const Filter&);
Filter &operator=(const Filter &);
bool operator==(const Filter &);
bool operator!=(const Filter &);
friend ostream &operator<<(ofstream &, const Filter&);
friend istream &operator>>(ifstream &, Filter& );
Filter &operator+=(char); // d<<"sda"- десен аргумент char добавя аргумента към края на низът за филтриране
Filter &operator+=(char* ); //- десен аргумент char* добавя дадения низ към края на низът за филтриране
Filter &operator|(const Filter &);  //- два аргумента Filter връща FilterChain съставен от аргументите си
~Filter();

//set/get methods
void set_word(char* );
void set_filtered(char*);
char* get_word() const;
char* get_filtered() const;

//read/write
void serialize(ofstream &) const;
void deserialize(ifstream &);

//filtering
bool filter(char*);

private:
//sydyrza dumata po koqto ste se filtrira
char* word;
//sydyrza stringa polu4avast se sled premahvaneto na vsqko srestane na word v nego
char* filtered;
};
