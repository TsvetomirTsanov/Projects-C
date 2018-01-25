#include <iostream>
#include <fstream>
#include <string>

#include "DynamicArray.h"
#include "Student.h"
#include "Helpers.h"

using namespace std;

/**<
1.Поне една “стабилна” и поне една “нестабилна” сортировка;           Merge, Radix
2.Поне една сортировка, която не използва сравнение между елементите; Radix
3.Две сортировки, които имат сложност по време Onnв общия случай;     Merge, Insertion
4.Поне една сортировка, която има най-лоша сложност по време Onn;     Merge
5.Една сортировка, която има линейна сложност по време;               Radix
6.Сортира в произволен ред (или низходящ, или възходящ);              Merge, Radix, Insertion
7.Да се реализира една сортировка със сложност по време Onn in-place: Insetion
 */

int main ( int argc, char *argv[] )
{
    DynamicArray sheet;

    if(argc != 4)
    {
        cout<<"Not 3 arguments! "<< endl;
        return -1;
    }

    ifstream stream(argv[1]);
    if (!stream.is_open())
    {
		std::cerr << "Can't open the file!\n";
		return -1;
	}
    else
    {
        char first_line[256];
        stream.getline(first_line,256);
        while(!stream.eof())
        {
            char name[256], subject[16], date[16];
            int age, grade;
            stream.getline(name, 255, ',');
            stream >> age;
            stream.ignore();
            stream.getline(subject, 15, ',');
            stream >> grade;
            stream.ignore();
            stream.getline(date, 15);

            Student student(name, age, subject, grade, date);
            sheet.add(student);
        }
         switch(caseChooser(argv[2]))
         {
             case 1 : MergeSort(sheet, argv[2], argv[3]);
                      break;
             case 2 : InsertionSort(sheet, argv[2],argv[3]);
                      break;
             case 3 : RadixSort(sheet, argv[2], argv[3]);
                      break;
             case 4 : cout <<"Incorrect input!:";
                      break;
         }

    }
    sheet.print();
    return 0;
}
