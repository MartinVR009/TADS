#include <iostream>

//Un comentario


template<typename T>
class BinaryNode
{
    private:
        T data;
        BinaryNode* left;
        BinaryNode* right;

    public:
    BinaryNode(){
        this->left = nullptr;
        this->right = nullptr;
    }

    BinaryNode(T data){
        this->left = nullptr;
        this->right = nullptr;
        this->data = data;
    }

    bool isEmpty(){
        if(this->left == nullptr && this->right == nullptr) return true;
        else return false;
    }

    BinaryNode* GetNewNode(T data)
    {
        BinaryNode* newNode = new BinaryNode();
        newNode->data = data;
        newNode->right = nullptr;
        newNode->left = nullptr;
        return newNode;
    }

    BinaryNode* Insert(BinaryNode*& root, T data){
        if(root == nullptr){
            root = GetNewNode(data);
        }else if(data < root->data){
            root->left = Insert(root->left, data);
        }else if(data > root->data){
            root->right = Insert(root->right, data);
        }else{
            return NULL;
        }
        return root;
    }

    bool search(BinaryNode* root, T data){
        if(root == nullptr) return false;
        if(root-> data == data) return true;
        else if(data < root-> data) return search(root->left, data);
        else return search(root->right, data);
    }

    T getData(){
        return this->data;
    }

    BinaryNode* rightChild(){
        return this->right;
    }

    BinaryNode* leftChild(){
        return this->left;
    }
    void changeData(T data){
        this->data = data;
    }

    void preOrder(BinaryNode* node){
        if(node != nullptr){
            std::cout<<node->data;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(BinaryNode* node){
        if(node != nullptr){
            posOrder(node->left);
            posOrder(node->right);
            std::cout<<node->data;
        }
    }
    void inOrder(BinaryNode* node){
        if(node != nullptr){
            inOrder(node->left);
            std::cout<<node->data;
            inOrder(node->right);
        }
    }
    

    void levelOrderTraversal(BinaryNode* node){
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
    int height(BinaryNode* root){
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

    int size(BinaryNode* root){
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
    BinaryNode<int>* root;
    root->Insert(root, 15);
    root->Insert(root, 20);
    root->Insert(root, 10);
    if(root->search(root, 10)) std::cout<<"Encontro \n";
    return 0;
}