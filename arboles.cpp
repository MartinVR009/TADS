#include <iostream>


struct BinaryNode
{
    int data;
    BinaryNode* left;
    BinaryNode* right;

};

BinaryNode* GetNewNode(int data)
    {
        BinaryNode* newNode = new BinaryNode();
        newNode->data = data;
        newNode->right = nullptr;
        newNode->left = nullptr;
        return newNode;
    }

BinaryNode* Insert(BinaryNode*& root, int data){
    if(root == nullptr){
        root = GetNewNode(data);
    }else if(data <= root->data){
        root->left = Insert(root->left, data);
    }else{
         root->right = Insert(root->right, data);
    }
    return root;
}

bool search(BinaryNode* root, int data){
    if(root == nullptr) return false;
    if(root-> data == data) return true;
    else if(data < root-> data) return search(root->left, data);
    else return search(root->right, data);
}


int main(){
    BinaryNode* root = nullptr;
    root = Insert(root, 15);
    root = Insert(root, 20);
    root = Insert(root, 10);
    if(search(root, 10)) std::cout<<"Encontro \n";
    return 0;
}