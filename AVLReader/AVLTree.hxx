#include "AVLTree.h"
#include "AVLNode.h"
#include <string>

        template<typename A>
        AVLTree<A>::AVLTree() {
            root = nullptr;
        }

        // Constructor con un solo argumento para inicializar con un valor
        template<typename A>
        AVLTree<A>::AVLTree(A var) {
            root->GetNewNode(var);
        }

        // Destructor para liberar la memoria asignada a los nodos AVL
        template<typename A>
        AVLTree<A>::~AVLTree() {
            deleteTree(root);
        }

        template<typename A>
        void AVLTree<A>::deleteTree(AVLNode<A>* node) {
            if (node != nullptr) {
                deleteTree(node->leftChild());
                deleteTree(node->rightChild());
                delete node;
            }
        }

        // Verificar si el árbol está vacío
        template<typename A>
        bool AVLTree<A>::isEmpty(){
            return root == nullptr;
        }

        template<typename A>
        int AVLTree<A>::height(){
            if(root != nullptr){
                return root->heightTree(root);
            }
            return 0;
        }

        template<typename A>
        bool AVLTree<A>::Insert(A data){
            if(search(data))
                return false;

            this->root = this->root->Insert(root, data);
            return true;
        }

        template<typename A>
        bool AVLTree<A>::Delete(A data){
            if(root != nullptr){
                if(root->Delete(root, data)!= nullptr)
                    return true;
            }
            return false;
        }

        template<typename A>
        A AVLTree<A>::getData(){
            return root->getData();
        }

        template<typename A>
        bool AVLTree<A>::search(A data){
            return root->search(root, data);
        }

        template<typename A>
        AVLNode<A>* AVLTree<A>::searchNodeX(A data) {
            return root->searchNode(root, data);
        }

        template<typename A>
        A AVLTree<A>::searchData(A data) {
            return root->searchData(root, data);
        }


        template<typename A>
        void AVLTree<A>::preOrder(){
            if(root != nullptr){
                root->preOrder(root);
            }
        }

        template<typename A>
        void AVLTree<A>::postOrder(){
            if(root != nullptr){
                root->postOrder(root);
            }
        }

        template<typename A>
        void AVLTree<A>::inOrder(){
            if(root != nullptr){
                root->inOrder(root);
            }
        }

        template<typename A>
        std::list<A> AVLTree<A>::inOrderList(){
            std::list<A> listaIn;
            root->inOrderList(root, listaIn);
            return listaIn;
        }

        template<typename A>
        std::list<A> AVLTree<A>::inOrderListPrefix(std::string prefix){
            std::list<A> listaIn;
            root->inOrderListPrefix(root, listaIn, prefix);
            return listaIn;
        }

        template<typename A>
        std::list<A> AVLTree<A>::inOrderListSufix(std::string sufix){
            std::list<A> listaIn;
            root->inOrderListSufix(root, listaIn, sufix);
            return listaIn;
        }

        template<typename A>
        void AVLTree<A>::levelOrderTraversal(){
            if(root != nullptr){
                root->levelOrderTraversal(root);
            }
        }

        template<typename A>
        void AVLTree<A>::print2D(int s){
            root->print2D(root, s);
        }

        template<typename A>
        int AVLTree<A>::size(){
            if(root != nullptr){
                return root->size(root);
            }
            return 0;
        }