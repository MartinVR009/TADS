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
            return node->left->height() - node->right->height();
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

    AVLNode* Insert(AVLNode*& root, T data){
        if(root == nullptr){
            root = GetNewNode(data);
        }else if(data < root->data){
            root->left = Insert(root->left, data);
        }else if(data > root->data){
            root->right = Insert(root->right, data);
        }else{
            return root;
        }

        //Update Height of current node        
         root->height = root->height() + 1;

        //Get balance factor
        int balanceFRoot = balanceFactor(root)

        //if BF > 1 
        if(balanceFRoot > 1){
            root = leftRotate(root);
            if(balanceFactor(root->right) < -1)
                root->right = rightRotate(root->right);
        }else if(balanceFRoot < -1){
            root = rightRotate(root);
            if(balanceFactor(root->left))
                root->left = leftRotate(root->left);
        }

        return root;
    }

    AVLNode* rightRotate(AVLNode* node){

        AVLNode* N1 = node->left;
        AVLNode* T2 = N1->right;

        N1->right = node;
        node->left = T2;
        
        node->height = max(height(node->left), height(node->right)) + 1;  
        N1->height = max(height(N1->left), height(N1->right)) + 1;

        return N1;    
    }
    AVLNode* leftRotate(AVLNode* node){

        AVLNode* N2 = node->right;
        AVLNode* T2 = node->left;

        N2->left = node;
        node->right = T2;

        N2->height = max(height(N2->left), height(N2->right)) + 1;
        node->height = max(height(node->left), height(node->right)) + 1;  

        return N2;
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
            std::cout<<node->data;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(AVLNode* node){
        if(node != nullptr){
            posOrder(node->left);
            posOrder(node->right);
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
    int height(AVLNode* root){
        if(root != nullptr){
            int maxHeight = 0;
            int leftSubTree = 0;
            int rightSubTree = 0;
            if(root->left != nullptr) leftSubTree = height(root->left);
            if(root->right != nullptr) rightSubTree = height(root->right);

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
    /*bool eliminar(T val)*/
};

template <typename A>
class BinaryTree
{
    private:
        AVLNode<int>* root;
    
    public:
        BinaryTree(): root(nullptr) {}
        BinaryTree(A var): root(GetNewNode(var)) {}

};

int main(){
    
    return 0;
}