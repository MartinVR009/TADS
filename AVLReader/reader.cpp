#include "AVLNode.h"
#include "AVLTree.h"
#include "wordTree.h"
#include "Library.h"
#include <stack>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>

using namespace std;

int main(){
    Library system;
    system.iniciar_arbol("words.txt");
    system.iniciar_arbol_reverso("words.txt");
    system.prefijos("hetero");
    system.sufijos("key");
    return 0;
}