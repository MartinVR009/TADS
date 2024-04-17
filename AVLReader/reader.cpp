#include "AVLNode.h"
#include "AVLTree.h"
#include "AVLNode.hxx"
#include "AVLTree.hxx"
#include <stack>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>


using namespace std;

template <typename K, typename V> struct keyValue {
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
    keyValue<char, AVLTree<std::string>> tree; //Una pareja donde la llave es un char 'a' y su valor es un AVL de palabras

    // Constructor
    WordTree() {}
    WordTree(char sm) {
        tree.key = sm;
    }

    AVLTree<std::string> getSubTree(){
        return tree.value;
    }
    // Funciones para operar en el árbol
    void insertWord(std::string word) {
        tree.value.Insert(word);
    }

    bool searchWord(std::string word) {
        return tree.value.search(word);
    }

    std::string returnWord(std::string word){
        return tree.value.searchData(word);
    }

    void printTree() {
        tree.value.inOrder();
    }

    bool operator==(WordTree &other){
        return tree.key == other.tree.key;
    }

    bool operator!=(WordTree &other){
        return tree.key != other.tree.key;
    }

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

    std::list<std::string> lookPrefix(std::string prefix){
        return tree.value.inOrderListPrefix(prefix);
    }

    std::list<std::string> lookSufix(std::string sufix){
        return tree.value.inOrderListSufix(sufix);
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

using wholeTree = AVLTree<WordTree>; //Es un arbol de WordTree's 

class Library{
    private:
        wholeTree original; 
        wholeTree reverse;
        bool original_ini = false;
        bool reverse_ini = false;
    public:
        Library(){
            for(char abc = 'a'; abc <= 'z'; abc++){
                
                original.Insert(WordTree(abc));
                reverse.Insert(WordTree(abc));
            }
        }

        std::string toLowerCase(const std::string& str) {
            std::string result = str; // Crear una copia del string original

            // Convertir cada carácter a minúscula
            for (char& c : result) {
                c = std::tolower(c);
            }

            return result;
        }

        int getPoints(std::string word) {
            int puntaje = 0;
            // Recorre cada caracter de la palabra
            for (char c : word) {
                if (std::toupper(c) == 'E' ||
                    std::toupper(c) == 'A' ||
                    std::toupper(c) == 'I' ||
                    std::toupper(c) == 'O' ||
                    std::toupper(c) == 'N' ||
                    std::toupper(c) == 'R' ||
                    std::toupper(c) == 'T' ||
                    std::toupper(c) == 'L' ||
                    std::toupper(c) == 'S' ||
                    std::toupper(c) == 'U') {
                    puntaje += 1;
                } else if (std::toupper(c) == 'D' || std::toupper(c) == 'G') {
                    puntaje += 2;
                } else if (std::toupper(c) == 'B' ||
                        std::toupper(c) == 'C' ||
                        std::toupper(c) == 'M' ||
                        std::toupper(c) == 'P') {
                    puntaje += 3;
                } else if (std::toupper(c) == 'F' ||
                        std::toupper(c) == 'H' ||
                        std::toupper(c) == 'V' ||
                        std::toupper(c) == 'W' ||
                        std::toupper(c) == 'Y') {
                    puntaje += 4;
                } else if (std::toupper(c) == 'K') {
                    puntaje += 5;
                } else if (std::toupper(c) == 'J' || std::toupper(c) == 'X') {
                    puntaje += 8;
                } else if (std::toupper(c) == 'Q' || std::toupper(c) == 'Z') {
                    puntaje += 10;
                }
            }
            return puntaje;
        }

        void InsertOriginal(std::string word){
            AVLNode<WordTree>* tempNode = original.searchNodeX(WordTree(tolower(word[0])));
            if(tempNode != nullptr){
                tempNode->data.insertWord(toLowerCase(word));
            }
        }

        void InsertReverse(std::string word){
            AVLNode<WordTree>* tempNode = reverse.searchNodeX(WordTree(tolower(word[0])));
            if(tempNode != nullptr){
                tempNode->data.insertWord(toLowerCase(word));
            }
        }

        void iniciar_arbol(std::string filename){
            if(original_ini){
                std::cout<<"El árbol del diccionario ya ha sido inicializado\n";
                return;
            }
            std::ifstream file(filename);

            if(!file.is_open()){
                std::cout<<"No se pudo abrir el archivo: " << filename <<"\n";
                return;
            }

            std::string word;

            while(file >> word){
                if(verifyWord(word)){
                    InsertOriginal(word);
                }
            }
            if(!original.isEmpty()){
                std::cout<<"El árbol del diccionario se ha inicializado correctamente\n";
                original_ini = true;
            }
            file.close();
        }

        void iniciar_arbol_reverso(std::string filename){
            if(reverse_ini){
                std::cout<<"El árbol del diccionario ya ha sido inicializado\n";
                return;
            }
            std::ifstream file(filename);

            if(!file.is_open()){
                std::cout<<"El archivo: " << filename <<" no existe o no puede ser leído \n";
                return;
            }

            std::string word;

            while(file >> word){
                if(verifyWord(word)){
                    word = reverseWord(word);
                    InsertReverse(word);
                }
            }
            if(!reverse.isEmpty()) {
                std::cout<<"El árbol del diccionario inverso se ha inicializado correctamente\n";
                reverse_ini = true;
            }
            file.close();
        }

        string reverseWord(string expression) { 
            std::stack<char> rWord; 
            for (char c : expression) 
                rWord.push(c);          
            string reverse = "";      
            while (!rWord.empty()) {  
                reverse += rWord.top(); 
                                        
                rWord.pop();            
            }
            return reverse; 
        }

        bool verifyWord(string expression) { 
            for (char c : expression) { //Recorrer expression
                if (!std::isalpha(c)) { // Si no es alfanumerico
                    return false;
                }
            }
            return true; // Si la palabra es válida se retorna true
        }

        void prefijos(std::string Prefix){
            Prefix = toLowerCase(Prefix);
            AVLNode<WordTree>* tempNode = original.searchNodeX(WordTree(tolower(Prefix[0])));

            std::list<std::string> lista_prefijos = tempNode->data.lookPrefix(Prefix);
            if(lista_prefijos.empty()){
                std::cout<<"No se hallaron palabras con ese prefijo\n";
                return;
            }
            std::cout<<"Palabras con prefijo: " << Prefix <<"\n";
            for(std::list<std::string>::iterator it = lista_prefijos.begin(); it != lista_prefijos.end(); it++){
                std::cout<<*it << " , longitud: " << it->size() << ", puntaje: " << getPoints(*it) <<"\n";
            }
            std::cout <<"\n-----------------------------------------\n";
        }

        void sufijos(std::string Sufix){
            Sufix = reverseWord(toLowerCase(Sufix));
            AVLNode<WordTree>* tempNode = reverse.searchNodeX(WordTree(tolower(Sufix[0])));

            std::list<std::string> lista_sufijos = tempNode->data.lookSufix(Sufix);
            if(lista_sufijos.empty()){
                std::cout<<"No se hallaron palabras con ese sufijo\n";
                return;
            }
            std::cout<<"Palabras con sufijo: " << reverseWord(Sufix) <<"\n";
            for(std::list<std::string>::iterator it = lista_sufijos.begin(); it != lista_sufijos.end(); it++){
                std::cout<<reverseWord(*it) << " , longitud: " << it->size() << ", puntaje: " << getPoints(*it) <<"\n";
            }
            std::cout <<"\n-----------------------------------------\n";
        }

};


int main(){
    Library system;

    system.iniciar_arbol("words.txt");
    system.iniciar_arbol_reverso("words.txt");
    system.prefijos("hetero");
    system.sufijos("key");
    return 0;
}