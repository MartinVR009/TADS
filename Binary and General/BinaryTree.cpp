#include <iostream>
#include <queue>
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

    BinaryNode* Delete(BinaryNode *root, int data) {
        // Return if the tree is empty
        if (root == nullptr) return root;

        // Find the node to be deleted
        if (data < root->data)
            root->left = Delete(root->left, data);
        else if (data > root->data)
            root->right = Delete(root->right, data);
        else {
            // If the node is with only one child or no child
            if (root->left == nullptr) {
                BinaryNode *temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                BinaryNode *temp = root->left;
                delete root;
                return temp;
            }

            // If the node has two children
            BinaryNode *temp = minLeftLeaf(root->right);

            root->data = temp->data;

            root->right = Delete(root->right, temp->data);
            }   
            return root;
        }

    BinaryNode* minLeftLeaf(BinaryNode* node){
            BinaryNode* current = node;

            while(current->left != nullptr)
            current = current->left;
            
            return current;
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
            postOrder(node->left);
            postOrder(node->right);
            std::cout<<node->data;
        }
    }
    void inOrder(BinaryNode* node){
        if(node != nullptr){
            inOrder(node->left);
            std::cout<<node->data<<" ";
            inOrder(node->right);
        }
    }
    

    void levelOrderTraversal(BinaryNode* node){
        std::queue<BinaryNode*> nodeQueue;
        nodeQueue.push(node);

        while(!nodeQueue.empty()){
            BinaryNode* temp = nodeQueue.front();
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

};

template <typename A>
class BinaryTree
{
    private:
        BinaryNode<A>* root;
    
    public:
        BinaryTree(){
            root = nullptr;
        }
        BinaryTree(A var){
            root->Insert(var);
        }
        ~BinaryTree() {
            deleteTree(root);
        }

        void deleteTree(BinaryNode<A>* node) {
            if (node != nullptr) {
                deleteTree(node->leftChild());
                deleteTree(node->rightChild());
                delete node;
            }
        }

        bool isEmpty() const {
            return root == nullptr;
        }

        int height(){
            if(root != nullptr){
                return root->height(root);
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
    BinaryTree<int> root;
    root.Insert(50);
    root.Insert(30);
    root.Insert(20);
    root.Insert(40);
    root.Insert(70);
    root.Insert(60);
    root.Insert(80);
    root.inOrder();
    root.Delete(50);
    std::cout<<"\n";
    root.inOrder();
    return 0;
}