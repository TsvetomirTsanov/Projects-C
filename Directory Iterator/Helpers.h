#ifndef HELPERS_H
#define HELPERS_H
#include "Tree.h"

void my_strncpy(char* dest, const char* source)
{
    for(int i = 0; source[i] != '*'; i++)
    {
        dest[i] = source[i];
    }
    dest[strlen(source)-1] = '\0';
}

bool extension_check(const char* file, const char* extension)
{
    int file_len = strlen(file);
    int ext_len = strlen(extension);
    while(ext_len && file[file_len] != '.')
    {
        if(extension[ext_len] != file[file_len])
            return false;

        ext_len--;
        file_len--;
    }
    return true;
}


void dir_iterator(TreeNode* tree)
{
        int count = 2; // for skipping hard links (. && ..)

        WIN32_FIND_DATA ffd;
        HANDLE hFind = FindFirstFile(tree->getData().getPath(), &ffd);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            std::cout << "FindFirstFile failed! Error code is " << GetLastError() << std::endl;
            //return 2;
        }
        else
        {
            do
            {
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) //folder
                {

                    if(count <= 0)
                    {
                        char* next_dir = new char[MAX_PATH + 3];
                        my_strncpy(next_dir, tree->getData().getPath());
                        strcat(next_dir, ffd.cFileName);
                        strcat(next_dir,"\\*");
                        File next_folder(ffd.cFileName, next_dir, 0);
                        tree->addFolder(next_folder);
                    }
                    count--;
                }
                else  // file
                {
//                    if(extension_check(ffd.cFileName, extension))
//                    {
                        File file(ffd.cFileName, tree->getData().getPath(), ffd.nFileSizeLow);
                        tree->addFile(file);
//                    }
                }
            }while (FindNextFile(hFind, &ffd) != 0);

            if (GetLastError() != ERROR_NO_MORE_FILES)
                std::cout << "FindNextFile failed! Error code is " << GetLastError() << std::endl;

            FindClose(hFind);
        }

        if(tree->getNumfolders()){
            for(int i = 0; i < tree->getNumfolders();i++)
                dir_iterator(tree->getFolder(i));

        }

}
void print(TreeNode* node)
{
    node->printFiles();
    if(node->getNumfolders())
    {
        for(int i = 0; i < node->getNumfolders(); i++)
            print(node->getFolder(i));
    }
}


void InsertionSort(vector<File*>& input)
{
    int n = input.size();

    for(int i = 1; i < n; i++)
    {
        File* temp = input[i];
        int hole = i;
        while(hole > 0 && input[hole-1]->getSize() <= temp->getSize())
        {
            if(input[hole-1]->getSize() == temp->getSize()
                                             && strcmp(input[hole-1]->getPath(), temp->getPath()) > 0)
            {
//                input.setFile(hole, input[hole-1])
                //input[hole] = input[hole-1];
                hole -= 1;
            }
            else
            {
//                input.setFile(hole, input[hole-1]);
                hole -= 1;
            }
        }
        input[hole] = temp;
    }
}
void filesystem_interface(TreeNode* tree)
{
    string command;
    bool flag = true;

    while(flag)
    {
        cout<<"Enter command(print,quit). " << endl;
        std::cin>>command;
        if(!command.compare("quit"))
            flag = false;
        else if(!command.compare("print"))
        {
           // InsertionSort(tree);
            print(tree);
        }
    }
}

#endif // HELPERS_H
