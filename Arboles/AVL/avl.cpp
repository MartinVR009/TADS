#include "AVLNode.h"
#include "AVLTree.h"
#include "AVLNode.hxx"
#include "AVLTree.hxx"
#include <iostream>
#include <iterator>

int main() {
    AVLTree<int> myTree;

    // Inserta algunos valores en el árbol
    myTree.Insert(10);
    myTree.Insert(5);
    myTree.Insert(15);
    myTree.Insert(2);
    myTree.Insert(7);
    myTree.inOrder();

    myTree.print2D(4);


    std::list<int> miLista;
    miLista = myTree.inOrderList();
    std::cout<<"\n In Order de la lista??!!? \n";
    for(std::list<int>::iterator it = miLista.begin(); it != miLista.end(); it++){
        std::cout<< *it << " ";
    }

    return 0;
}

