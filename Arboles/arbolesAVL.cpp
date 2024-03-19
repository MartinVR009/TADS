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
    AVLNode():left(nullptr), right(nullptr), height(0) {}

    AVLNode(T data): data(data), left(nullptr), right(nullptr), height(0) {}

    ~AVLNode(){
        if(left != nullptr){
            delete left;
            left = nullptr;
        }
        if(right != nullptr){
            delete right;
            right = nullptr;
        }
    }

    bool isEmpty(){
        if(this->left == nullptr && this->right == nullptr) return true;
        else return false;
    }

    int max(int a, int b){
        return (a > b) ? a : b;
    }

    int balanceFactor(AVLNode* node){
        if(node == nullptr){
            return 0;
        }else{
            return node->left->height - node->right->height;
        }
    }

    AVLNode* GetNewNode(T data)
    {
        AVLNode* newNode = new AVLNode();
        newNode->data = data;
        newNode->height = 0;
        newNode->right = nullptr;
        newNode->left = nullptr;
        return newNode;
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


    AVLNode* Insert(AVLNode*& root, T data) {
        if (root == nullptr) {
            root = GetNewNode(data);
        } else if (data < root->data) {
            root->left = Insert(root->left, data);
        } else if (data > root->data) {
            root->right = Insert(root->right, data);
        }else {
            return nullptr;
        }

        /*
        // Actualizar la altura del nodo actual
        if (root != nullptr) {
            root->height = 1 + max(heightTree(root->left), heightTree(root->right));
        }
        */
        // Obtener el factor de equilibrio
        int balanceFRoot = balanceFactor(root);

        // Rebalancear el árbol si es necesario
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

    AVLNode* Delete(AVLNode*& root, T data){

        if (root == nullptr) 
            return NULL; 

        //Search of data
        if ( data < root->data ) 
            root->left = Delete(root->left, data); 
        else if( data > root->data ) 
            root->right = Delete(root->right, data); 
        else{ //If found data
            //Case 2 and 1, 1 Child or no child
            if (root->left == nullptr) {
                AVLNode *temp = root->right;
                free(root);
                return temp;
            }else if(root->right == nullptr) {
                AVLNode *temp = root->left;
                free(root);
                return temp;
            }
            //Case 3, 2 Childs
            AVLNode *temp = minLeftLeaf(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }

        root->height = 1 +  max(root->left->height, root->right->height);
        //Get balance factor
        int balanceFRoot = balanceFactor(root);
        /*
        if(balanceFRoot > 1 ){
            if (data < root->left->data) {
                return rightRotate(root);
            }else if (data > root->left->data){
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }else if(balanceFRoot < -1){
            if (data > root->right->data){
                return leftRotate(root);
            }else if (data < root->right->data){
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        */

        return root;
    }


    AVLNode* minLeftLeaf(AVLNode* node){
        AVLNode* current = node;

        while(current->left != nullptr)
           current = current->left;
        
        return current;
    }

    AVLNode* rightRotate(AVLNode* node){
        if(node != nullptr){
            AVLNode* N1 = node->left;
            AVLNode* T2 = N1->right;

            N1->right = node;
            node->left = T2;
            
            node->height = max(heightTree(node->left), heightTree(node->right)) + 1;  
            N1->height = max(heightTree(N1->left), heightTree(N1->right)) + 1;

            return N1; 
        }
        return node;   
    }
    AVLNode* leftRotate(AVLNode* node){
        if(node != nullptr){
            AVLNode* N2 = node->right;
            AVLNode* T2 = node->left;

            N2->left = node;
            node->right = T2;

            N2->height = max(heightTree(N2->left), heightTree(N2->right)) + 1;
            node->height = max(heightTree(node->left), heightTree(node->right)) + 1;  

            return N2;
        }
        return node;
    }

    AVLNode* search(AVLNode* root, T data){
        if(root == nullptr) return NULL;
        if(root-> data == data) return root;
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
            std::cout<<node->data;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(AVLNode* node){
        if(node != nullptr){
            postOrder(node->left);
            postOrder(node->right);
            std::cout<<node->data;
        }
    }
    void inOrder(AVLNode* node){
        if(node != nullptr){
            inOrder(node->left);
            std::cout<<node->data;
            inOrder(node->right);
        }
    }
    

    void levelOrderTraversal(AVLNode* node){
        std::queue<AVLNode*> nodeQueue;
        nodeQueue.push(node);

        while(!nodeQueue.empty()){
            AVLNode* temp = nodeQueue.front();
            nodeQueue.pop();
            std::cout<<temp->data<< " ";
            if(temp->left != nullptr) nodeQueue.push(temp->left);
            if(temp->right != nullptr) nodeQueue.push(temp->right);
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
                return root->heightTree();
            }
            return 0;
        }

        bool Insert(A data){
            if(root->Insert(root, data) != nullptr)
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
    myTree.Insert(16);
    return 0;
}