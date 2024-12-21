#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

class Node {
    public:
        int value;
        Node* left;
        Node* right;
        int height;

        Node(int val): value(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
    public:
        Node* root;
       
        AVLTree() {
            root = nullptr;
        }

       int getBalance(Node* root) {
            if (root == nullptr) {
                return 0;
            }
            return getHeight(root->left) - getHeight(root->right);
       }

        Node* rightRotate(Node* y) {
            if(y == nullptr || y->left == nullptr) {
                return y;
            }
            
            Node* x = y->left;
            Node* T2 = x->right;

            x->right = y;
            y->left = T2;

            y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
            x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

            return x;
        }

        Node* leftRotate(Node* x) {
            Node* y = x->right;
            Node* T2 = y->left;

            y->left = x;
            x->right = T2;

            x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
            y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

            return x;
        }


        Node* insert(Node* root, int val) {
            if (root == nullptr) {
                root = new Node(val);
                root->value = val;
                root->left = nullptr;
                root->right = nullptr;
                return root;
                }

            if(val < root->value) {
                root->left = insert(root->left, val);
            } else if (val > root->value) {
                root->right = insert(root->right, val);
            } else {
                return root;
            }

            root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
            int balance = getBalance(root);

            if (balance > 1 && val < (root->left)->value) {
                return rightRotate(root);
            }

            if (balance < -1 && val > (root->right)->value) {
                return leftRotate(root);
            }

            if (balance > 1 && val > (root->left)->value) {
                return rightRotate(root);
            }

            if (balance < -1 && val < (root->right)->value) {
                return leftRotate(root);
            }

            return root;
        }

        bool search(Node* root, int key) {
            if (root == nullptr) {
            return false; 
            }

            if (root->key == key) {
            return true; 
            }
            
            if (key < root->key) {
            return search(root->left, key);
            }
                
            else if (key > root-> key) {
            return search(root->right, key);
            }
        }

        int getHeight(Node* root){
            if(root == nullptr) {
                return 0;
            }
           return root->height;
        }

        Node* deleteNode(Node* root, int key) {
            if(root == nullptr) {
                return root;
            }

            if (key < (root->value)) {
                root->left = deleteNode(root->left, key);
            } else if (key > (root->value)) {
                root->right = deleteNode(root->right, key);
            } else {
                if(root->left == nullptr) {
                    Node* temp = root->right;
                    root = NULL;
                    return temp;
                } else if (root->right == nullptr) {
                    Node* temp = root->left;
                    root = NULL;
                    return temp;
                }
            }

            Node* temp = getMinValueNode(root->right);
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->value);

            root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

            int balance = getBalance(root);

            if (balance > 1 && getBalance(root->left) >= 0) {
                return rightRotate(root);
            }

            if (balance > 1 && getBalance(root->left) < 0) {
                return leftRotate(root);
            }

            if (balance < -1 && getBalance(root->right) <= 0) {
                return leftRotate(root);
            }

            if (balance < -1 && getBalance(root->right) > 0) {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }

            return root;

        }

        Node* getMinValueNode(Node* node) {
            Node* current = node;
            while(current->left != nullptr) {
                current = current->left;
            }
            return current;
        }

        void printAVLTree(Node* root) {
            cout << "Which method? " << endl;
            cout << "A. pre-order" << endl;
            cout << "B. level-based" << endl;
            cout << "C. ascending order" << endl;

            string input;
            cin >> input;

            if(input == "A") {
                preOrderTraversal(root);
            } else if (input == "B") {
                LevelOrder(root);
            } else if (input == "C") {
                AscendingOrder(root);
            }
        }

        void preOrderTraversal(Node* root) {
            if(root == nullptr) {
                return;
            } 
            cout << root->value << " ";
            preOrderTraversal(root->left);
            preOrderTraversal(root->right);
        }

        void LevelOrder(Node* root) {
               if (root == nullptr){
                     return;
                }   

                vector<Node*> currentLevel = {root};  
                while (!currentLevel.empty()) {
                vector<Node*> nextLevel;
                for (Node* node : currentLevel) {
                     if (node) {
                        cout << node->value << " ";
                        nextLevel.push_back(node->left);
                        nextLevel.push_back(node->right);
                            } else {
                                cout << "null "; 
                                }
                        }
        cout << endl;
        currentLevel = nextLevel;
                    }               
        }

        void AscendingOrder(Node* root) {
            if (root == nullptr) {
                return;
            } 
            AscendingOrder(root->left);
            cout << root->value << " ";
            AscendingOrder(root->right);
        }

};

int main() {
    AVLTree star;
    int input;
    cout << "Enter values (ENTER -1 to stop): " << endl;
   
    while (true) {
        cin >> input;
        if (input == -1) {
            break;
        }
        star.root = star.insert(star.root, input);
    }

    cout << "Would you like the print the AVL Tree? " << endl;
    string yesorNo;
    cin >> yesorNo;

    if(yesorNo == "yes") {
        star.printAVLTree(star.root);
    }

    return 0;
}
