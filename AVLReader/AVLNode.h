#ifndef AVLNODE_H
#define AVLNODE_H
#define SPACE 6

#include <list>
#include<string>

template<typename T>
class AVLNode
{
    public:
        T data;
        AVLNode* left;
        AVLNode* right;

        AVLNode();
        AVLNode(T data);
        bool isEmpty();
        AVLNode* GetNewNode(T data);
        int max(T a, T b);
        AVLNode* Insert(AVLNode* &root, const T&data);
        AVLNode* Delete(AVLNode* &root, const T&data);
        AVLNode* minLeftLeaf(AVLNode* node);
        bool search(AVLNode* root, T data);
        //Additional reader function
        AVLNode* searchNode(AVLNode* root, T data); 
        T searchData(AVLNode* root, T data); 

        T getData();
        AVLNode* rightChild();
        AVLNode* leftChild();
        void changeData(T data);
        void preOrder(AVLNode* node);
        void postOrder(AVLNode* node);
        void inOrder(AVLNode* node);
        void inOrderList(AVLNode* node, std::list<T> &listaRe);
        void inOrderListPrefix(AVLNode* node, std::list<T> &listaRe, std::string prefix);
        void inOrderListSufix(AVLNode* node, std::list<T> &listaRe, std::string sufix);
        void levelOrderTraversal(AVLNode* node);
        int heightTree(AVLNode* root);
        int size(AVLNode* root);
        //AVL Functions
        int Balance(AVLNode* nod);
        AVLNode* rightRotate(AVLNode* y);
        AVLNode* leftRotate(AVLNode * x);
        void print2D(AVLNode* r, int space);
};


#endif // AVLNODE_H