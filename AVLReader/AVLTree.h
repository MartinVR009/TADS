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
    A getData();
    void deleteTree(AVLNode<A>* node);
    void deleteTree();
    bool isEmpty();
    int height();
    bool Insert(A data);
    bool Delete(A data);
    bool search(A data);
    AVLNode<A>* searchNodeX(A data);
    A searchData(A data);
    void preOrder();
    void postOrder();
    void inOrder();
    std::list<A> inOrderList();
    std::list<A> inOrderListPrefix(std::string prefix);
    std::list<A> inOrderListSufix(std::string sufix);
    void levelOrderTraversal();
    void print2D(int s);
    int size();
};


#endif // AVLTREE_H
