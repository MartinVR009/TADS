#ifndef WORDTREE_H
#define WORDTREE_H

#include "AVLNode.h"
#include "AVLTree.h"
#include "AVLNode.hxx"
#include "AVLTree.hxx"
#include <stack>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>

template <typename K, typename V> 
struct keyValue {
  K key;
  V value;

  keyValue(K key, V value) : key(key), value() {}
  keyValue(K key) : key(key), value() {}
  keyValue() {}

    bool operator==(keyValue<K,V> &other){
        return this->key == other.key;
    }

    bool operator!=(keyValue<K,V> &other){
        return this->key != other.key;
    }

    bool operator<(const keyValue<K,V> &other) const {
        return this->key < other.key;
    }

    bool operator>(const keyValue<K,V> &other) const {
        return this->key > other.key;
    }

    keyValue &operator=(const keyValue<K, V> other) {
        this->key = other.key;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const keyValue<K, V> other) {
        os << "Key:" << other.key;
        return os;
    }

};

class WordTree {
    public:
        keyValue<char, AVLTree<std::string>> tree;

        WordTree();
        WordTree(char sm);
        AVLTree<std::string> getSubTree();
        void insertWord(std::string word);
        bool searchWord(std::string word);
        std::string returnWord(std::string word);
        void printTree();
        std::list<std::string> lookPrefix(std::string prefix);
        std::list<std::string> lookSufix(std::string sufix);
        bool operator==(const WordTree &other) const;
        bool operator!=(const WordTree &other) const;

        bool operator<(const WordTree &other) const {
            return tree.key < other.tree.key;
        }

        bool operator>(const WordTree &other) const {
            return tree.key > other.tree.key;
        }

        WordTree &operator=(const WordTree other) {
            this->tree.key = other.tree.key;
            return *this;
        }

        friend class AVLTree<WordTree>; 
        friend class AVLNode<WordTree>; 
        friend std::ostream &operator<<(std::ostream &os, const WordTree &other);

};

std::ostream &operator<<(std::ostream &os, const WordTree &other) {
    os << "Key:" << other.tree.key;
    os << "\n Subtree: \n";
    return os;
}

#include "wordTree.hxx"


#endif