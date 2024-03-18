#include <iostream>
#include <queue>


template<typename T>
class AVLNode
{
    private:
        T data;
        AVLNode* left;
        AVLNode* right;

    public:
    AVLNode():left(nullptr), right(nullptr) {}

    AVLNode(T data): data(data), left(nullptr), right(nullptr) {}

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
        
        int height = root->height();
        //Update Height of current node

        //Get balance factor
        int bf = balanceFactor(root)

        //if BF > 1 
        if(bf > 1){
            //LeftRotate(root)
            //BF < -1
                    //RightRotate(root->left)
        }else if(bf < -1){

        }
        //if BF < -1
            //RightRotate(root)
            //if Bf > 1
                //LeftRotate(root->right)




        return root;
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
    AVLNode<int>* root = nullptr;
    root->Insert(root, 15);
    root->Insert(root, 20);
    root->Insert(root, 10);
    if(root->search(root, 10)) std::cout<<"Encontro \n";
    std::cout<<"Altura: " << root->height(root);
    std::cout<<"Tamanio: " << root->size(root);
    return 0;
}