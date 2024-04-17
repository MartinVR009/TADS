#include "AVLNode.h"

#include <iostream>
#include <queue>

        std::string toLowerCase(const std::string& str) {
            std::string result = str; // Crear una copia del string original

            // Convertir cada carácter a minúscula
            for (char& c : result) {
                c = std::tolower(c);
            }

            return result;
        }

        bool Prefix(std::string word,std::string prefix){
            int tam = prefix.size();
            word = toLowerCase(word);
            if(word.size() >= tam){
                for(int i = 0; i < tam; i++){
                    if(word[i] == prefix[i]){
                        continue;
                    }else{
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        template<typename T>
        AVLNode<T>::AVLNode(){
            this->left = nullptr;
            this->right = nullptr;
        }

        template<typename T>
        AVLNode<T>::AVLNode(T data){
            this->left = nullptr;
            this->right = nullptr;
            this->data = data;
        }

        template<typename T>
        bool AVLNode<T>::isEmpty(){
            if(this->left == nullptr && this->right == nullptr) return true;
            else return false;
        }

        template<typename T>
        AVLNode<T>* AVLNode<T>::GetNewNode(T data)
        {
            AVLNode<T>* newNode = new AVLNode();
            newNode->data = data;
            newNode->right = nullptr;
            newNode->left = nullptr;
            return newNode;
        }

        template<typename T>
        int AVLNode<T>::max(T a, T b){
            return (a > b) ? a : b;
        }

        template<typename T>
        AVLNode<T>* AVLNode<T>:: Insert(AVLNode<T>* &root, const T &data){

            if(search(root, data)){
                return NULL;
            }

            if(root == nullptr)
                return GetNewNode(data);
            
            if(data < root->data){
                root->left = Insert(root->left, data);
            }else if(data > root->data){
                root->right = Insert(root->right, data);
            }else{
                return root;
            }

            int balance = Balance(root); 
            
            //Left Left Case
            if (balance > 1 && data < root -> left -> data){
                return rightRotate(root);
            }
                

            // Right Right Case  
            if (balance  < -1 && data > root -> right -> data){
                return leftRotate(root);
            }
            // Left Right Case  
            if (balance > 1 && data > root -> left -> data) {
                root-> left = leftRotate(root -> left);
                return rightRotate(root);
            }

              // Right Left Case  
            if (balance < -1 && data< root-> right -> data) {
                root-> right = rightRotate(root -> right);
                return leftRotate(root);
            }

            return root; 
        }

        template<typename T>
        AVLNode<T>* AVLNode<T>::Delete(AVLNode<T>* &root, const T &data) {
            if (root == nullptr) return root;

            // Find the node 
            if (data < root->data)
                root->left = Delete(root->left, data);
            else if (data > root->data)
                root->right = Delete(root->right, data);
            else {
                    if(root->left == nullptr) {
                        // If the node is with only one child or no child (root->left == nullptr) 
                            AVLNode *temp = root->right;
                            delete root;
                            return temp;
                    }
                    if (root->right == nullptr) {
                            AVLNode *temp = root->right;
                            delete root;
                            return temp;
                    }
                    if(root->right != nullptr && root->left != nullptr){ //Case 3: 2 children
                            AVLNode *temp = minLeftLeaf(root->right);
                            root->data = temp->data;
                            root->right = Delete(root->right, temp->data);
                    }
                }   
            
            int balance = Balance(root);

            //Left Left Case
            if (balance == 2 && Balance(root->left) >= 0){
                root = rightRotate(root);
                  
            }else if (balance == 2 && Balance(root->left) == -1){  // Left Right Case 
                root->left = leftRotate(root->left);
                root = rightRotate(root);
            }
            // Left Left Case  
            else if(balance == -2 && Balance(root->right) <= 0 ) {
                root = leftRotate(root);
            }else if(balance == -2 && Balance(root->right) == 1){
                root->right = rightRotate(root->right);
                root = leftRotate(root);
            } 
            return root;
        }

        template<typename T>
        AVLNode<T>* AVLNode<T>::minLeftLeaf(AVLNode<T>* node){
                AVLNode<T>* current = node;

                while(current->left != nullptr)
                current = current->left;
                
                return current;
            }

        template<typename T>
        bool AVLNode<T>::search(AVLNode<T>* root, T data){
            if(root == nullptr) return false;
            if(root-> data == data) {
                return true;
            }
            else if(data < root-> data) return search(root->left, data);
            else return search(root->right, data);
        }

        //Reader Function
        template<typename A>
        AVLNode<A>* AVLNode<A>::searchNode(AVLNode<A>* root, A data){
            if(root == nullptr) return nullptr;
            if(root->data == data) {
                return root;
            }
            else if(data < root->data){
                return searchNode(root->left, data);
            }
            else {
                return searchNode(root->right, data);
            }
        }


        template<typename T>
        T AVLNode<T>::searchData(AVLNode<T>* root, T data){
            if(root == nullptr) return NULL;
            if(root-> data == data) {
                return root->data;
            }
            else if(data < root-> data) return searchData(root->left, data);
            else return searchData(root->right, data);
        }

        template<typename T>
        T AVLNode<T>::getData(){
            return this->data;
        }

        template<typename T>
        AVLNode<T>* AVLNode<T>::rightChild(){
            return this->right;
        }
        
        template<typename T>
        AVLNode<T>* AVLNode<T>::leftChild(){
            return this->left;
        }

        template<typename T>
        void AVLNode<T>::changeData(T data){
            this->data = data;
        }

        template<typename T>
        void AVLNode<T>::preOrder(AVLNode<T>* node){
            if(node != nullptr){
                std::cout<<node->data<<" ";
                preOrder(node->left);
                preOrder(node->right);
            }
        } 
        
        template<typename T>
        void AVLNode<T>::postOrder(AVLNode<T>* node){
            if(node != nullptr){
                postOrder(node->left);
                postOrder(node->right);
                std::cout<<node->data <<" ";
            }
        }

        template<typename T>
        void AVLNode<T>::inOrder(AVLNode<T>* node){
            if(node != nullptr){
                inOrder(node->left);
                std::cout<<node->data <<" ";
                inOrder(node->right);
            }
        }

        template<typename T>
        void AVLNode<T>::inOrderList(AVLNode<T>* node, std::list<T> &listaRe){
            if(node != nullptr){
                inOrderList(node->left, listaRe);
                listaRe.push_back(node->data);
                inOrderList(node->right, listaRe);
            }
        }

        template<typename T>
        void AVLNode<T>::inOrderListPrefix(AVLNode<T>* node, std::list<T> &listaRe, std::string prefix){
            if(node != nullptr){
                inOrderListPrefix(node->left, listaRe, prefix);
                if(Prefix(node->data, prefix)){
                    listaRe.push_back(node->data);
                }
                inOrderListPrefix(node->right, listaRe, prefix);
            }
        }

        template<typename T>
        void AVLNode<T>::inOrderListSufix(AVLNode<T>* node, std::list<T> &listaRe, std::string sufix){
            if(node != nullptr){
                inOrderListSufix(node->left, listaRe, sufix);
                if(Prefix(node->data, sufix)){
                    listaRe.push_back(node->data);
                }
                inOrderListSufix(node->right, listaRe, sufix);
            }
        }
        
        template<typename T>
        void AVLNode<T>::levelOrderTraversal(AVLNode<T>* node) {
            if (node == nullptr)
                return;

            std::queue<AVLNode<T>*> nodeQueue;
            nodeQueue.push(node);

            while (!nodeQueue.empty()) {
                int levelSize = nodeQueue.size();
                
                for (int i = 0; i < levelSize; ++i) {
                    AVLNode<T>* currNode = nodeQueue.front();
                    nodeQueue.pop();
                    std::cout<<currNode->data<< " ";
                    if (currNode->left != nullptr)
                        nodeQueue.push(currNode->left);
                    if (currNode->right != nullptr)
                        nodeQueue.push(currNode->right);
                }
            }
        }

        template<typename T>
        int AVLNode<T>::heightTree(AVLNode<T>* root){
            if(root != nullptr){
                int maxHeight = 0;
                int leftSubTree = 0;
                int rightSubTree = 0;
                if(root->left != nullptr) leftSubTree = heightTree(root->left);
                if(root->right != nullptr) rightSubTree = heightTree(root->right);

                if(leftSubTree > rightSubTree)
                    maxHeight = leftSubTree;
                else
                    maxHeight = rightSubTree; 
                return maxHeight + 1;
            }else{
                return 0;
            }  
        }   

        template<typename T>
        int AVLNode<T>::size(AVLNode<T>* root){
            if(root == nullptr)
                return 0;

            int leftSubTree = size(root->left);
            int rightSubTree = size(root->right);

            int sum = leftSubTree + rightSubTree + 1 ;
            return sum;
        }

        //AVL Additional Functions

        template<typename T>
        int AVLNode<T>::Balance(AVLNode<T>* nod){
           if (nod == nullptr) 
                return 0; 
            return heightTree(nod->left) - heightTree(nod->right); 
            
        }

        template<typename T>
        AVLNode<T>* AVLNode<T>::rightRotate(AVLNode<T>* y){
           /*AVLNode<T>* father = y->left;
            y->left = father->right;
            father->right = y;
            //print2D(father, 4);
            return father;*/
            
            AVLNode*x = y->left;
            AVLNode* T1 = x->right;

            x->right =y;
            y->left = T1;

            return x;

        }

        template<typename T>
        AVLNode<T>* AVLNode<T>::leftRotate(AVLNode<T>* x){
            /*AVLNode<T>* father = x->right;
            x->right = father->left;
            father->left = x;
            //print2D(father, 4);
            return father;*/
            AVLNode *y = x->right; 
            AVLNode *T2 = y->left; 

                // Perform rotation 
            y->left = x; 
            x->right = T2; 
                // Return new root 
            return y; 
        }

        template<typename T>
        void AVLNode<T>::print2D(AVLNode * r, int space) {
            if (r == nullptr) // Base case  1
                return;
            space += SPACE; // Increase distance between levels   2
            print2D(r -> right, space); // Process right child first 3 
            std::cout <<std:: endl;
            for (int i = SPACE; i < space; i++) // 5 
            std::cout << " "; // 5.1  
            std::cout << r -> data << "\n"; // 6
            print2D(r -> left, space);
        }