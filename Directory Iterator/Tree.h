#ifndef TREE_H
#define TREE_H

#include <cstddef>
#include <vector>
#include "File.h"

using namespace std;


class TreeNode {

private:
    TreeNode* parent;
    File folder;
    vector<TreeNode*> subfolders;
    vector<File*> files;

public:

    TreeNode(TreeNode* parent, const File&);
    ~TreeNode();

    File getData() const;
    void setData(const File& data);
    void addFolder(const File& data);
    void addFile(const File& data);
    void setFile(const size_t& indx, const File*);
//    TreeNode* findFolder(const File& data) const;
    TreeNode* getFolder(const size_t& indx) const;
    TreeNode* getParent() const;
    int getNumfolders() const;
    void printFiles() const;
    //void print(const TreeNode*) const;

};
#endif // TREE_H
