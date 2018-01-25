#include <iostream>
#include <windows.h>
#include <string>
#include <queue>

#include "File.h"

#include "Helpers.h"
#include "Tree.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "Usage: " << argv[0] << " <path>\n\n";
		return 1;
	}

	std::cout << "Scanning " << argv[1] << "...\n";

    char* path = new char[MAX_PATH + 3];

	strncpy(path, argv[1], MAX_PATH);
	strncat(path, "\\*" ,MAX_PATH);

    File root_directory("root", path, 0);
    TreeNode* root = new TreeNode(NULL, root_directory);
	dir_iterator(root);
    filesystem_interface(root);
    delete root;
	return 0;
}
