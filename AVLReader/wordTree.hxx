#include "wordTree.h"

    WordTree::WordTree(){}

    WordTree::WordTree(char sm){
        tree.key = sm;
    }

    AVLTree<std::string> WordTree::getSubTree(){
        return tree.value;
    }

    void WordTree::insertWord(std::string word){
        tree.value.Insert(word);
    }

    bool WordTree::searchWord(std::string word){
        return tree.value.search(word);
    }

    void WordTree::printTree(){
        tree.value.inOrder();
    }

    std::list<std::string> WordTree::lookPrefix(std::string prefix){
        return tree.value.inOrderListPrefix(prefix);
    }

    std::list<std::string> WordTree::lookSufix(std::string sufix){
        return tree.value.inOrderListSufix(sufix);
    }


    bool WordTree::operator==(const WordTree& b) const{
        return this->tree.key == b.tree.key;
    }