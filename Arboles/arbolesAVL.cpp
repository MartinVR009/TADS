#include <iostream>
#include <queue>


template<typename T>
class AVLNode
{
    private:
        T data;
        AVLNode* left;
        AVLNode* right;
        int height;

    public:
        AVLNode(){
            this->left = nullptr;
            this->right = nullptr;
            this->height = 0;
        }

        AVLNode(T data){
            this->left = nullptr;
            this->right = nullptr;
            this->data = data;
            this->height = 0;
        }

        bool isEmpty(){
            if(this->left == nullptr && this->right == nullptr) return true;
            else return false;
        }

        AVLNode* GetNewNode(T data)
        {
            AVLNode* newNode = new AVLNode();
            newNode->data = data;
            newNode->right = nullptr;
            newNode->left = nullptr;
            return newNode;
        }

        int max(int a, int b){
            return (a > b) ? a : b;
        }

        AVLNode* Insert(AVLNode*& root, T data){
            if(root == nullptr){
                root = GetNewNode(data);
            }else if(data < root->data){
                root->left = Insert(root->left, data);
            }else if(data > root->data){
                root->right = Insert(root->right, data);
            }else{
                return NULL;
            }

            root->height = 1 + max(heightTree(root->left), heightTree(root->right));
            
            int balanceFRoot = balanceFactor(root);

            if(balanceFRoot > 1 ){
                if (data < root->left->data) {
                    root= rightRotate(root);
                }else if (data > root->left->data){
                    root->left = leftRotate(root->left);
                    root = rightRotate(root);
                }
            }else if(balanceFRoot < -1){
                if (data > root->right->data){
                    root = leftRotate(root);
                }else if (data < root->right->data){
                    root->right = rightRotate(root->right);
                    root = leftRotate(root);
                }
            }

            return root;
        }

        AVLNode* Delete(AVLNode *root, int data) {
            if (root == NULL) return root;

            // Find the node 
            if (data < root->data)
                root->left = Delete(root->left, data);
            else if (data > root->data)
                root->right = Delete(root->right, data);
            else {
                // If the node is with only one child or no child
                if (root->left == NULL) {
                    AVLNode *temp = root->right;
                    free(root);
                    return temp;
                } else if (root->right == NULL) {
                    AVLNode *temp = root->left;
                    free(root);
                    return temp;
                }

                AVLNode *temp = minLeftLeaf(root->right);
                root->data = temp->data;
                root->right = Delete(root->right, temp->data);
                }   

                root->height = 1 + max(heightTree(root->left), heightTree(root->right));
            
            int balanceFRoot = balanceFactor(root);

             if (balanceFRoot > 1) {
                if (balanceFactor(root->left) >= 0) {
                    return rightRotate(root);
                } else {
                    root->left = leftRotate(root->left);
                    return rightRotate(root);
                }
            }
            if (balanceFRoot < -1) {
                if (balanceFactor(root->right) <= 0) {
                    return leftRotate(root);
                } else {
                    root->right = rightRotate(root->right);
                    return leftRotate(root);
                }
            }
            return root;
        }

        AVLNode* minLeftLeaf(AVLNode* node){
                AVLNode* current = node;

                while(current->left != nullptr)
                current = current->left;
                
                return current;
            }

        bool search(AVLNode* root, T data){
            if(root == nullptr) return false;
            if(root-> data == data) return true;
            else if(data < root-> data) return search(root->left, data);
            else return search(root->right, data);
        }

        T getData(){
            return this->data;
        }

        AVLNode* rightChild(){
            return this->right;
        }

        AVLNode* leftChild(){
            return this->left;
        }
        void changeData(T data){
            this->data = data;
        }

        void preOrder(AVLNode* node){
            if(node != nullptr){
                std::cout<<node->data<<" ";
                preOrder(node->left);
                preOrder(node->right);
            }
        }

        void postOrder(AVLNode* node){
            if(node != nullptr){
                postOrder(node->left);
                postOrder(node->right);
                std::cout<<node->data <<" ";
            }
        }
        void inOrder(AVLNode* node){
            if(node != nullptr){
                inOrder(node->left);
                std::cout<<node->data <<" ";
                inOrder(node->right);
            }
        }
        

        void levelOrderTraversal(AVLNode* root) {
            if (root == nullptr)
                return;

            std::queue<AVLNode*> nodeQueue;
            nodeQueue.push(root);

            while (!nodeQueue.empty()) {
                int levelSize = nodeQueue.size();

                for (int i = 0; i < levelSize; ++i) {
                    AVLNode* currNode = nodeQueue.front();
                    nodeQueue.pop();
                    std::cout << currNode->data << " ";

                    if (currNode->left != nullptr)
                        nodeQueue.push(currNode->left);
                    if (currNode->right != nullptr)
                        nodeQueue.push(currNode->right);
                }
            }
        }

        int heightTree(AVLNode* root){
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

        int size(AVLNode* root){
            if(root == nullptr)
                return 0;

            int leftSubTree = size(root->left);
            int rightSubTree = size(root->right);

            int sum = leftSubTree + rightSubTree + 1 ;
            return sum;
        }

        //Funciones Adicionales AVL

        int balanceFactor(AVLNode* node){
            if(node == nullptr){
                return 0;
            }else{
                return heightTree(node->left) - heightTree(node->right);
            }
        }

        AVLNode* rightRotate(AVLNode* node){
            
                AVLNode* N1 = node->left;
                AVLNode* T2 = N1->right;

                N1->right = node;
                node->left = T2;
                
                node->height = max(heightTree(node->left), heightTree(node->right)) + 1;  
                N1->height = max(heightTree(N1->left), heightTree(N1->right)) + 1;

                return N1; 
            
            return node;   
        }
        AVLNode* leftRotate(AVLNode* node){
            
                AVLNode* N2 = node->right;
                AVLNode* T2 = node->left;

                N2->left = node;
                node->right = T2;

                N2->height = max(heightTree(N2->left), heightTree(N2->right)) + 1;
                node->height = max(heightTree(node->left), heightTree(node->right)) + 1;  

                return N2;
           
            return node;
        }


};

template <typename A>
class AVLTree {
    private:
        AVLNode<A>* root;

    public:
        // Constructor predeterminado
        AVLTree() {
            root = nullptr;
        }

        // Constructor con un solo argumento para inicializar con un valor
        AVLTree(A var) {
            root->Insert(var);
        }

        // Destructor para liberar la memoria asignada a los nodos AVL
        ~AVLTree() {
            deleteTree(root);
        }

        void deleteTree(AVLNode<A>* node) {
            if (node != nullptr) {
                deleteTree(node->leftChild());
                deleteTree(node->rightChild());
                delete node;
            }
        }

        // Verificar si el árbol está vacío
        bool isEmpty() const {
            return root == nullptr;
        }

        int height(){
            if(root != nullptr){
                return root->heightTree(root);
            }
            return 0;
        }

        bool Insert(A data){
            if(root->Insert(root, data) != NULL)
                return true;
            return false;
        }

        bool Delete(A data){
            if(root != nullptr){
                if(root->Delete(root, data)!= NULL)
                    return true;
            }
            return false;
        }

        bool search(A data){
            if(root != nullptr){
                if(root->search(root, data) != NULL)
                    return true;
            }
            return false;
        }

        void preOrder(){
            if(root != nullptr){
                root->preOrder(root);
            }
        }
        void postOrder(){
            if(root != nullptr){
                root->postOrder(root);
            }
        }
        void inOrder(){
            if(root != nullptr){
                root->inOrder(root);
            }
        }
        void levelOrderTraversal(){
            if(root != nullptr){
                root->levelOrderTraversal(root);
            }
        }
        int size(){
            if(root != nullptr){
                return root->size(root);
            }
            return 0;
        }
};

int main(){
    AVLTree<int> myTree;
    myTree.Insert(9);
    myTree.Insert(5);
    myTree.Insert(10);
    myTree.Insert(0);
    myTree.Insert(6);
    myTree.Insert(11);
    myTree.Insert(-1);
    myTree.Insert(1);
    myTree.Insert(2);
    myTree.levelOrderTraversal();
    std::cout<<std::endl;
    myTree.postOrder();
    std::cout<<"\n Pre Delete In order traversal \n";
    myTree.Delete(10);
    myTree.levelOrderTraversal();
    std::cout<<"\n Pos Delete In order traversal \n";
    return 0;
}


