#include <iostream>
#include <cstdlib>
using namespace std;

template<typename Key, typename Value>

class TreapMap {

private:
    struct Node {
        Key key;
        Value value;
        int priority;
        Node* left;
        Node* right;

        Node(const Key& k, const Value& v, int p)
            : key(k), value(v), priority(p), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int node_count;

    void rotateRight(Node*& y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        y = x;
    }

    void rotateLeft(Node*& x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        x = y;
    }

    void insert(Node*& root, const Key& key, const Value& value) {
        if(root==nullptr){
            root= new Node(key,value,rand());
            node_count++;
            return;
        }
        if(key < root->key) {
            insert(root->left, key, value);
            if (root->left && root->left->priority > root->priority) {
                rotateRight(root);
            }
        }else if (key > root->key) {
            insert(root->right, key, value);
            if (root->right && root->right->priority > root->priority) {
                rotateLeft(root);
            }
        } else {
            
            root->value = value;
        }
    }

    void remove(Node*& root, const Key& key) {
        if (root == nullptr) return;

        if (key < root->key) remove(root->left, key);
        else if (key > root->key) remove(root->right, key);
        else {
           
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                root = nullptr;
                node_count--;
            } else if (root->left == nullptr) {
                rotateLeft(root);
                remove(root->left, key);
            } else if (root->right == nullptr) {
                rotateRight(root);
                remove(root->right, key);
            } else {
                if (root->left->priority > root->right->priority) {
                    rotateRight(root);
                } else {
                    rotateLeft(root);
                }
                remove(root, key);
            }
        }
    }

    const Value* findPtr(Node* root, const Key& key) const {
        if (root == nullptr) {
            return nullptr;
        } else if (key == root->key) {
            return &root->value;
        } else if (key < root->key) {
            return findPtr(root->left, key);
        } else {
            return findPtr(root->right, key);
        }
    }

    void clear(Node* root) {
        if (root == nullptr) return;
        clear(root->left);
        clear(root->right);
        delete root;
    }

public:
    TreapMap() : root(nullptr), node_count(0) {
        
        srand(time(nullptr));
    }

    ~TreapMap() { clear(root); }

    int size() const { return node_count; }

    
    void insert(const Key& key, const Value& value) { insert(root, key, value); }

    
    void remove(const Key& key) { remove(root, key); }

    bool member(const Key& key) const { return findPtr(root, key) != nullptr; }

    Value find(const Key& key, const Value& v) const {
        const Value* p = findPtr(root, key);
        if (p) {
            return *p;
        } else {
            return v;
        }
    }


};