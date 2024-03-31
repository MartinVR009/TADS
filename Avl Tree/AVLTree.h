#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <list>
#include <string>

template <typename A>
class AVLTree {
public:
    AVLNode<A>* root = nullptr;

    AVLTree();
    AVLTree(A var);
    ~AVLTree();
    void deleteTree(AVLNode<A>* node);
    void deleteTree();
    bool isEmpty();
    int height();
    bool Insert(A data);
    bool Delete(A data);
    bool search(A data);
    void preOrder();
    void postOrder();
    void inOrder();
    std::list<A> inOrderList();
    void levelOrderTraversal();
    void print2D(int s);
    int size();
};


#endif // AVLTREE_H
