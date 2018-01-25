#include "Tree.h"


TreeNode::TreeNode(TreeNode* parent,const File& folder_info) : parent(parent), folder(folder_info) {
    //this->data = new T(data);
    //files.push_back(data);
}


TreeNode::~TreeNode() {
    for(int i = 0; i< files.size(); i++)
        delete files[i];
    for(int i = 0; i< subfolders.size(); i++)
        delete subfolders[i];
}


File TreeNode::getData() const {
    return folder;
}


void TreeNode::setData(const File& data) {
//    for(int i=0; i<files.size(); i++)
//        if(files[i]->getName() == data.getName())
//            return files[i];
    folder = data;
}


void TreeNode::addFolder(const File& new_folder) {
    subfolders.push_back(new TreeNode(this, new_folder));
}


void TreeNode::addFile(const File& data)
{
    files.push_back(new File(data));
}


//void TreeNode::setFile(const size_t& indx, const File* other) {
//    files[indx] = other;
//}


//TreeNode& TreeNode::findFolder(const File& data) const {
//    for(int i=0; i<subfolders.size(); i++)
//        if(subfolders[i]->getData() == data)
//            return subfolders[i];
//    return NULL;
//}


TreeNode* TreeNode::getFolder(const size_t& indx) const {
    return subfolders[indx];
}


TreeNode* TreeNode::getParent() const {
    return parent;
}


int TreeNode::getNumfolders() const {
    return subfolders.size();
}


void TreeNode::printFiles() const
{
    for(int i = 0; i < files.size(); i++)
        files[i]->print();
}


