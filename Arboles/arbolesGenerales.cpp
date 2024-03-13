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

        std::list<Node*> getDesc(){
            return desc;
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

        int size(Node* node){
            if(node == nullptr){
                return 0;
            }else{
                subSize = 0;
                descIterator it;
                for(it = node->desc.begin(); it != node->desc.end(); it++){
                    subSize += size(*it);
                }
                return subSize + 1;
            }
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

                descIterator it;
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
                descIterator it;
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

        void levelOrderTraversal(Node* node){
            if(node == nullptr)
                return;
            
            std::queue<Node*> levelOrderQ;
            levelOrderQ.push(node);

            while(!levelOrderQ.empty()){
                Node * temp = levelOrderQ.front();
                levelOrderQ.pop();
                std::cout<<temp->data << " ";

                descIterator it = temp->desc.begin();
                for(; it != temp->desc.end(); it++)
                    levelOrderQ.push(*it);
                
                std::cout<<"\n";
            }
        }

        bool addNode(Node* &node, A father, A var){
            if(node == nullptr){
                return false;
            }else{ 
                if(node->data == father){
                     node->addDesc(var);
                    return true
                }else{
                    descIterator it;
                    for(it = node->desc.begin(); it != node->desc.end(); it++){
                        if((*it)->addNode(*it, father, var))
                            return true;
                    }
                    return false;
                }
            }
        }

        

        bool search(Node* node, A var){
            if(node == nullptr){
                return false;
            }else{
                if(node->data == var){
                    return true;
                }else{
                    descIterator it = node->desc.begin();
                    for(; it != node->desc.end(); it++){
                        if((*it)->search(*it, var)) return true;
                    }
                    return false;
                }
                
            }
        }
};


template <typename T>
class Tree{
    Node<T>* root = nullptr;
    bool isEmpty(){return root == nullptr;}

    Node<T>* getRoot(){
        return root;
    }

    void newRoot(Node<T>* nroot){
        root = nroot;
    }

    unsigned int altura(){
        return root->height();
    } 

    unsigned int size(){
        return root->size(*root);
    }

    bool addNode(T father, T n){
        if(!isEmpty()){
            return root->addNode(*root, father, n);
        }else{
            root = root->GetNewNode(n);
            return true;
        }
    }

    /*
    bool insertarNodo(T padre, T n);
    bool eliminarNodo(T n); 

    */
    bool search(T n){
        return root->search(*root,n);
    }

    void preOrder(){
        root->preOrder(*root);
    }

    void postOrder(){
        root->postOrder(*root);
    }

    void levelOrderTraversal(){
        root->levelOrderTraversal(*root);
    } 

};

int main(){
    return 0;
}