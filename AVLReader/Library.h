#ifndef LIBRARY_H
#define LIBRARY_H

#include "AVLNode.h"
#include "AVLTree.h"
#include "wordTree.h"
#include <stack>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>

using wholeTree = AVLTree<WordTree>;

class Library{
    public:
        wholeTree original; 
        wholeTree reverse;
        bool original_ini = false;
        bool reverse_ini = false;
    //Methods
    Library();
    std::string toLowerCase(const std::string& str);
    int getPoints(std::string word);
    void InsertOriginal(std::string word);
    void InsertReverse(std::string word);
    void iniciar_arbol(std::string filename);
    void iniciar_arbol_reverso(std::string filename);
    std::string reverseWord(std::string expression);
    bool verifyWord(std::string expression);
    void prefijos(std::string Prefix);
    void sufijos(std::string Sufix);

};

#include "Library.hxx"

#endif