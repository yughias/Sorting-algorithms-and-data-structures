#ifndef BST
#define BST

#include <iostream> 

using namespace std;

template<class T>
class BinarySearchTree{
private:
    struct Node{
        T label;
        Node* left; 
        Node* right;

        Node() : left(nullptr), right(nullptr) {}
        Node(T val) : label(val), left(nullptr), right(nullptr){}
    };

    Node* root;

    void inorder(Node* node){
        if(!node)
            return;
        inorder(node->left);
        cout << node->label << " ";
        inorder(node->right);
    }
    
    void preorder(Node* node){
        if(!node)
            return;
        cout << node->label << " ";
        preorder(node->left);
        preorder(node->right);
    }
    
    void postorder(Node* node){
        if(!node)
            return;
        postorder(node->left);
        postorder(node->right);
        cout << node->label << " ";
    }

    void add(Node*& node, T value){
        if(!node){
            node = new Node(value);
            return;
        }
        if(value > node->label)
            add(node->right, value);
        else
            add(node->left, value);
    }

    void delMin(Node*& node, T& value){
        if(node->left)
            delMin(node->left, value);
        else {
            value = node->label;
            Node* tmp = node;
            node = node->right;
            delete tmp;
        }
    }

    void del(Node*& node, T value){
        if(node){
            if(value < node->label){
                del(node->left, value); return;
            }
            if(value > node->label){
                del(node->right, value); return;
            }
            if(!node->left){
                Node* tmp = node;
                node = node->right;
                delete tmp;
                return;
            }
            if(!node->right){
                Node* tmp = node;
                node = node->left;
                delete tmp;
                return; 
            }
            delMin(node->right, node->label);
        }      
    }

    bool find(Node* node, T value){
        if(!node)
            return false;
        if(node->label == value)
            return true;
        if(value > node->label)
            return find(node->right, value);
        else
            return find(node->left, value);
    }

    void copy(Node*& node, T* arr, int& index){
        if(!node)
            return;
        copy(node->left, arr, index);
        arr[index++] = node->label;
        copy(node->right, arr, index);    
    }

public:
    BinarySearchTree(){ root = nullptr; }
    
    BinarySearchTree(T* arr, int len){
        root = nullptr;
        for(int i = 0; i < len; i++)
            add(root, arr[i]);
    }
    
    BinarySearchTree& add(T value){ add(root, value); return *this; }

    BinarySearchTree& del(T value){ del(root, value); return *this;}

    void preorder() { preorder(root); cout << endl; }
    
    void inorder() { inorder(root); cout << endl; }
    
    void postorder() { postorder(root); cout << endl; }

    bool find(T value){ return find(root, value); } 

    void copy(T* arr){
        int index = 0;
        copy(root, arr, index);
    }

    friend ostream& operator<<(ostream& os, BinarySearchTree bst){
        bst.inorder();
        return os;
    }
};

#endif