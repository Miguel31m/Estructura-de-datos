#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T>
class TreapSet {
private:

    struct Node{
        T key;
        int priority;
        Node* left;  //izq
        Node* right;  //right

        Node(const T& k, int p) : key(k), priority(p), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int node_count; //contador elementos en el conjunto
    
    void rotateRight(Node*& y) {
        Node* x= y->left;
        y->left = x->right;
        x->right = y;
        y= x;
    }

    void rotateLeft(Node*& x) {
        Node* y = x->right;
        x->right= y->left;
        y->left= x;
        x=y;
    }

    void insert(Node*& root, const T& key){
        if(root==nullptr) {
            root= new Node(key, rand());
            node_count++;
            return;
        }

        if(key < root->key) {
            insert(root->left,key);

            if(root->left && root->left->priority > root->priority){
                rotateRight(root);
            }
        }
        else if (key > root->key) {
            insert(root->right, key);

            if(root->right && root->right->priority > root->priority){
                rotateLeft(root);
            }
        }

        // si ket == root->Key no se hace nada pq no se admite duplicados
    }


    void remove(Node*& root, const T& key){

        if (root==nullptr) return;

        if(key < root->key) remove(root->left, key);

        else if (key > root->key) remove(root->right, key);

        else{

            if(root->left==nullptr && root->right==nullptr){
                delete root;
                root= nullptr;
                node_count--;
            }

            else if (root->left==nullptr){
                rotateLeft(root);
                remove(root->left,key);
            }

            else if(root->right==nullptr){
                rotateRight(root);
                remove(root->right , key);
            }
            else{
                if(root->left->priority > root->right->priority){

                    rotateRight(root);
                }else{

                    rotateLeft(root);
                }

                remove(root,key);

            }
        }
    }

    bool member(Node* root, const T& key) const{
        if(root==nullptr) return false;

        if(key==root->key) return true;

        if(key < root->key){
            return member(root->left, key);
        }else{
            return member(root->right, key);
        }
    }

    void clear(Node* root){
        if(root==nullptr) return;
        clear(root->left);
        clear(root->right);
        delete root;
    }

public:

    TreapSet(): root(nullptr), node_count(0) { srand(time(nullptr));}

    ~TreapSet() { clear(root); }

    int size() const { return node_count; }

    void insert(const T& key) { insert(root, key); }

    void remove(const T& key) { remove(root, key); }

    bool member(const T& key) const { return member(root, key); }

};
