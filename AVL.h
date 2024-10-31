#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string name;
    int ufid;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
private:
    int height(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    };

    int max(int a, int b) {
        if (a > b)
            return a;
        return b;
    };

    int getBalance(Node* N) {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    };

    Node* newNode(string name, string ufid) {
        Node* node = new Node();
        node->name = name;
        node->ufid = stoi(ufid);
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        // cout << "NODE INSERTED\n" << "name: " << node->name << endl << "ufid: " << node->ufid << endl << "height: " << node->height << endl;
        return(node);
    }

    Node* rightRotate(Node* y) {
        Node *x = y->left;
        Node *z = x->right;

        x->right = y;
        y->left = z;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    };

    Node* leftRotate(Node* x) {
        Node *y = x->right;
        Node *z = y->left;

        y->left = x;
        x->right = z;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;  
    };

    Node* insertHelper(Node* node, string studentName, string studentId) {
        if (node == nullptr) {
            cout << "successful\n";
            return(newNode(studentName, studentId));
        }
        if (stoi(studentId) < node->ufid)
            node->left = insertHelper(node->left, studentName, studentId);
        else if (stoi(studentId) > node->ufid)
            node->right = insertHelper(node->right, studentName, studentId);
        else {
            cout << "unsuccessful\n";
            return node;
        }
    
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && stoi(studentId) < node->left->ufid)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && stoi(studentId) > node->right->ufid)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && stoi(studentId) > node->left->ufid)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && stoi(studentId) < node->right->ufid)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    };

    Node* removeHelper(Node* node, int ufid);
    /* Node* removeHelper(Node* node, int ufid) {
        if(node != nullptr) {
           if(node->ufid == ufid) {
                // no child case
                if (node->left == nullptr && node->right == nullptr)
                    delete &node; // OR TRY node = nullptr;
                else if(node->left != nullptr && node->right != nullptr)

                cout << "successful\n"; return;
            }
            else{
                removeHelper(node->left, ufid);
                removeHelper(node->right, ufid);
            } 
        }
    }; */
    
    void searchIDHelper(Node* node, int ufid) {
        if(node != nullptr) {
            if(node->ufid == ufid) {cout << node->name << endl; return;}
            else{
                searchIDHelper(node->left, ufid);
                searchIDHelper(node->right, ufid);
            }
        }
    };
    
    void searchNameHelper(Node* node, string name) {
        if(node != nullptr) {
            if(node->name == name)
                cout << node->ufid << endl;
            searchNameHelper(node->left, name);
            searchNameHelper(node->right, name);
        }
    };

public:
    Node* root;
    
    void insert(string name, string ufid) {
        this->root = insertHelper(root, name, ufid);
    }
    
    void remove(string ufid) {
        this->root = removeHelper(this->root, this->root->ufid);
    }
    
    void searchID(int ufid) {
        searchIDHelper(this->root, ufid);
    }
    
    void searchName(string name) {
        searchNameHelper(this->root, name);
    }
    
    void removeInorder(int n) {
        
    }

    void printPreorder(Node* root) {
        if(root != nullptr) {
            cout << root->name;
            if (root->left != nullptr) {
                cout << ", ";
                printPreorder(root->left);
            }
            if (root->right != nullptr) {
                cout << ", ";
                printPreorder(root->right);
            }
        }
    };

    void printInorder(Node* root) {
        if(root != nullptr) {
            if (root->left != nullptr) {
                printInorder(root->left);
                cout << ", ";
            }
            cout << root->name;
            if (root->right != nullptr) {
                cout << ", ";
                printInorder(root->right);
            }
        }
    };

    void printPostorder(Node* root) {
        if(root != nullptr) {
            if (root->left != nullptr) {
                printPostorder(root->left);
                cout << ", ";
            }
            if (root->right != nullptr) {
                printPostorder(root->right);
                cout << ", ";
            }
            cout << root->name;
        }
    };

    void printLevelCount(Node* root) {
        cout << height(root) << endl;
    };

    bool inTree(Node* node, int ufid) {
        if (node == nullptr)
            return false;
        Node* x = node;
        while(x != nullptr) {
            if (x->ufid == ufid)
                return true;
            else if (x->ufid > ufid) 
                x = x->left;
            else if (x->ufid < ufid)
                x = x->right;

        }
        return false;
    };

    bool inTree(Node* node, string name) {
        if (node == nullptr)
            return false;
        Node* x = node;
        if (x->name == name)
            return true;
        return (inTree(x->left, name) || inTree(x->right, name));
    };

    AVLTree() : root() {}
};
