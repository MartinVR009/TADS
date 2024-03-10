#include <iostream>
#include <list>
#include <queue>

template <typename A>
class Node{
    protected:
        A data;
        std::list<Node*> desc;

        using descIterator = typename std::list<Node*>::iterator;

    public:
        Node(){desc.clear();}

        ~Node(){
            for(auto it = desc.begin(); it != desc.end(); it++){
                delete *it;
            }
            desc.clear();
        }



        Node* GetNewNode(A &var){
            Node* temp = new Node*;
            temp->data = var;
            return temp;
        }

        Node* GetNewNode(std::list<Node*> auxDesc){
            Node* temp = new Node*;
            temp->desc = auxDesc;
            return temp;
        }

        A &getData(){
            return data;
        }

        void setData(A &var){
            data = var;
        }   
        
        void clearList(){
            desc.clear();
        }

        void addDesc(A &var){
            desc.push_back(GetNewNode(var));
        }

        bool deleteDesc(A &val){
            descIterator it;
            bool found = false;
            for(it = desc.begin(); it != desc.end(); it++){
                if((*it)->data == val){
                    found = true; 
                    break;
                }
            }
            if(found){
                delete *it;
                this->desc.erase(it);
            }
            return found;
        }

        bool isLeaf(){
            return desc.empty();
        }

        int height(){ 

            if(isLeaf()){
                return 0; 
            }   

            int maxHeight = 0;
            descIterator it;
            for(it = desc.begin(); it != desc.end(); it++){
                int num = (*it)->height();
                if(num > maxHeight) {
                    maxHeight = num;
                }
            }

            return maxHeight + 1;
        }

        /*void preOrden();*/
        /*Procedimiento preOrden(nodo):
        Si nodo no es nulo:
            // Paso 1: Visitar el nodo actual
            Realizar operaciones con nodo

            // Paso 2: Recorrer los descendientes en preorden
            Para cada descendiente en la lista de descendientes de nodo:
                preOrden(descendiente)
        */

        void preOrder(Node* node){
            if(node != NULL){
                std::cout<<node->data<<"\n";

                descIterator = it;
                for(it = node->desc.begin(); it!= node->desc.end(); it++){
                    (*it)->preOrder(*it);
                }
            }
        }

        /*Procedimiento postOrden(nodo):
    Si nodo no es nulo:
        // Paso 1: Recorrer los descendientes en postorden
        Para cada descendiente en la lista de descendientes de nodo:
            postOrden(descendiente)

        // Paso 2: Visitar el nodo actual
        Realizar operaciones con nodo*/

        void postOrder(Node* node){
            if(node != NULL){
                descIterator = it;
                for(it = node->desc.begin(); it!= node->desc.end(); it++){
                    (*it)->postOrder(*it);
                }
                std::cout<<node->data<<"\n";
            }
        }
        /*Procedimiento nivelOrden(nodo):
        Si nodo no es nulo:
            1. Crear una cola vacía.
            2. Encolar el nodo raíz.
            3. Mientras la cola no esté vacía:
                a. Desencolar un nodo y visitarlo.
                b. Encolar todos los descendientes del nodo desencolado.
        */

        void levelOrderTrasversal(Node* node){
            if(node == NULL)
                return;
            
            std::queue<Node*> levelOrderQ;
            levelOrderQ.push(node);

            while(!levelOrderQ.empty()){
                
            }
        }
};


template <typename T>
class Tree{
    struct Node<T>* root = NULL;
    bool isEmpty(){return root == NULL;}

    void fijarRaiz(Node<T>* nraiz){
        
    }

    unsigned int altura(){
        if(isEmpty){
            return -1;
        }else{
            return root->altura(0);
        }
    }

    /*NodoGeneral<T>* obtenerRaiz();
    void fijarRaiz(NodoGeneral<T>* nraiz);
    bool insertarNodo(T padre, T n);
    bool eliminarNodo(T n); 
    bool buscar(T n);
    unsigned int tamano();
    void preOrden();
    void posOrden();
    void nivelOrden();*/

};

int main(){
    return 0;
}