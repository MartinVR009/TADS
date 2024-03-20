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
        AVLNode(){
            this->left = nullptr;
            this->right = nullptr;
        }

        AVLNode(T data){
            this->left = nullptr;
            this->right = nullptr;
            this->data = data;
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

        AVLNode* Insert(AVLNode* root, const T &data){

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
                std::cout<<"L-L case \n";
                return rightRotate(root);
            }
                

            // Right Right Case  
            if (balance  < -1 && data > root -> right -> data){
                std::cout<<"R-R case \n";
                return leftRotate(root);
            }
            // Left Right Case  
            if (balance > 1 && data > root -> left -> data) {
                std::cout<<"L-R case \n";
                root-> left = leftRotate(root -> left);
                return rightRotate(root);
            }

              // Right Left Case  
            if (balance < -1 && data< root-> right -> data) {
                std::cout<<"R-L case \n";
                root-> right = rightRotate(root -> right);
                return leftRotate(root);
            }

            return root; 
        }

        AVLNode* Delete(AVLNode *root, const T &data) {
            if (root == nullptr) return root;

            // Find the node 
            if (data < root->data)
                root->left = Delete(root->left, data);
            else if (data > root->data)
                root->right = Delete(root->right, data);
            else {
                //No child or Leaf
                if(root->left==nullptr && root ->right ==nullptr ){
                    root = nullptr;
                    delete root;
                }else if(root->left == nullptr) {
                // If the node is with only one child or no child (root->left == nullptr) {
                    AVLNode *temp = root->right;
                    *temp = *root;
                    delete temp;
                } else if (root->right == nullptr) {
                    AVLNode *temp = root->right;
                    *temp = *root;
                    delete temp;
                }
                    AVLNode *temp = minLeftLeaf(root->right);
                    root->data = temp->data;
                    root->right = Delete(root->right, temp->data);
                }   
            
            int balance = Balance(root);

            if (balance > 1 && data < root -> left -> data)
                  return rightRotate(root);

            // Right Right Case  
            if (balance  < -1 && data > root -> right -> data)
                return leftRotate(root);

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

        AVLNode* minLeftLeaf(AVLNode* node){
                AVLNode* current = node;

                while(current->left != nullptr)
                current = current->left;
                
                return current;
            }

        bool search(AVLNode* root, T data){
            if(root == nullptr) return false;
            if(root-> data == data) {
                std::cout<<" \n El numero " << data << "Ya estaba en la lista! \n";
                return true;
            }
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

        //AVL Additional Functions

        int Balance(AVLNode* nod){
           if (nod == nullptr) 
                return 0; 
            return heightTree(nod->left) - heightTree(nod->right); 
            
        }

        AVLNode* rightRotate(AVLNode* y){
            
                AVLNode *x = y->left; 
                AVLNode *T2 = x->right; 

                // Perform rotation 
                x->right = y; 
                y->left = T2; 
                return x;  
        }
        AVLNode* leftRotate(AVLNode* x){
            
                AVLNode *y = x->right; 
                AVLNode *T2 = y->left; 

                // Perform rotation 
                y->left = x; 
                x->right = T2; 
                // Return new root 
                return y; 
        }
};

template <typename A>
class AVLTree {
    public:
        AVLNode<A>* root = nullptr;

        // Constructor predeterminado
        AVLTree() {
            root = nullptr;
        }

        // Constructor con un solo argumento para inicializar con un valor
        AVLTree(A var) {
            root->GetNewNode(var);
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
            if(search(data))
                return false;

            this->root = this->root->Insert(root, data);
            return true;
        }

        bool Delete(A data){
            if(root != nullptr){
                if(root->Delete(root, data)!= NULL)
                    return true;
            }
            return false;
        }

        bool search(A data){
            return root->search(root, data);
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
    AVLNode<int>* root = nullptr;
    std::cout<<"\n";
    //root->levelOrderTraversal(root);
    std::cout<<"-----Arbol----- \n";
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
    myTree.Delete(2);
    std::cout<<"\n Pos Delete In order traversal \n";
    myTree.levelOrderTraversal();
    std::cout<<"\n";
    return 0;
}


