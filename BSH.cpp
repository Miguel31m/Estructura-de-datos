
#ifndef __BST_HH__
#define __BST_HH__

#include <iomanip>
#include <iostream>
#include <queue>


/**
 * Key: Type of the key
 * Value: Type of the value
 */
template <typename Key, typename Value> class BST {
private:
  class Node {
  private:
    Key key;
    Value value;
    Node *left;
    Node *right;

  public:
    Node(const Key &k, const Value &v)
        : key(k), value(v), left(nullptr), right(nullptr) {}
    const Key &getKey() const { return key; }
    bool hasLeft() const { return left != nullptr; }
    bool hasRight() const { return right != nullptr; }
    Node *getLeft() const { return left; }
    Node *getRight() const { return right; }
    void setLeft(Node *n) { left = n; }
    void setRight(Node *n) { right = n; }
    void setValue(const Value &v) { value = v; }
  };

private:
  Node *root;
  unsigned int sz;

public:
  BST() : root(nullptr), sz(0) {}
   BST(const BST &other) : root(nullptr), sz(0) {
    root = clone(other.root);
    sz = other.sz;
  }

  ~BST() {
    clear(root);
    }

  unsigned int size() const { return sz; }
  bool empty() const { return root == nullptr; }

  void insert(const Key &k, const Value &v) {
    if (empty()) {
      root = new Node(k, v);
      sz++;
      return;
    } else {
      insert(root, k, v);
    }
  }

private:
  void insert(Node *node, const Key &k, const Value &v) {
    if (k < node->getKey()) {
      if (node->hasLeft()) {
        insert(node->getLeft(), k, v);
      } else {
        Node *newNode = new Node(k, v);
        node->setLeft(newNode);
        sz++;
      }
    } else if (node->getKey() < k) {
      if (node->hasRight()) {
        insert(node->getRight(), k, v);
      } else {
        Node *newNode = new Node(k, v);
        node->setRight(newNode);
        sz++;
      }
    } else {
      // k already exists in the tree, update value
      node->setValue(v);
    }
  }

public:
  bool find(const Key &k) const {
    if (empty()) {
      return false;
    }
    return find(root, k);
  }

private:
  bool find(Node *node, const Key &k) const {
    if (node == nullptr)
      return false;
    else if (k < node->getKey())
      return find(node->getLeft(), k);
    else if (node->getKey() < k)
      return find(node->getRight(), k);
    else
      return true;
  }

  void clear(Node *node) {
    if (node != nullptr) {
        clear(node->getLeft());   
        clear(node->getRight());  
        delete node;              
        }
 }
 Node* clone(Node *node) {
    if (node == nullptr) return nullptr;
    Node *newNode = new Node(node->getKey(), node->value);
    newNode->setLeft(clone(node->getLeft()));
    newNode->setRight(clone(node->getRight()));
    return newNode;
  }

public:
  bool Search(const Value &v) {
    if (empty()) return false;
    return Search(root, v);
  }

private:
   bool Search(Node *node, const Value &v) const {
    if (node == nullptr) return false;

    if (node->value == v) return true;

    
    return Search(node->getLeft(), v) || Search(node->getRight(), v);
  }

  

  Node* findMin(Node* node) {
    while (node->hasLeft()) {
      node = node->getLeft();
    }
    return node;
  }

  Node* findMax(Node* node){
    while(node->hasRight()){
        node = node->getRight();
    }
    return node;
  }

public:
  int height() const {
    return height(root);
  }

private:
  int height(Node* node) const {
    if (node == nullptr) return -1; // árbol vacío → -1

    int leftHeight = height(node->getLeft());
    int rightHeight = height(node->getRight());

    if (leftHeight > rightHeight) {
      return 1 + leftHeight;
    } else {
      return 1 + rightHeight;
    }
  }

public:
  int countNodes() const {
    return countNodes(root);
  }

private:
  int countNodes(Node* node) const {
    if (node == nullptr) return 0;

    int leftCount = countNodes(node->getLeft());
    int rightCount = countNodes(node->getRight());

    return 1 + leftCount + rightCount;
  }

public:
  // Recorridos públicos
  void inorder() const {
    inorder(root);
    cout << endl;
  }

  void preorder() const {
    preorder(root);
    cout << endl;
  }

  void postorder() const {
    postorder(root);
    cout << endl;
  }

  void levelOrder() const {
    levelOrder(root);
    cout << endl;
  }

private:
  // --- Inorder (izquierda, raíz, derecha)
  void inorder(Node* node) const {
    if (node == nullptr) return;
    inorder(node->getLeft());
    cout << node->getKey() << " ";
    inorder(node->getRight());
  }

  // --- Preorder (raíz, izquierda, derecha)
  void preorder(Node* node) const {
    if (node == nullptr) return;
    cout << node->getKey() << " ";
    preorder(node->getLeft());
    preorder(node->getRight());
  }

  // --- Postorder (izquierda, derecha, raíz)
  void postorder(Node* node) const {
    if (node == nullptr) return;
    postorder(node->getLeft());
    postorder(node->getRight());
    cout << node->getKey() << " ";
  }

  // --- Level-order (BFS con cola)
  void levelOrder(Node* node) const {
    if (node == nullptr) return;

    queue<Node*> q;
    q.push(node);

    while (!q.empty()) {
      Node* current = q.front();
      q.pop();
      cout << current->getKey() << " ";

      if (current->hasLeft()) q.push(current->getLeft());
      if (current->hasRight()) q.push(current->getRight());
    }
  }

public:
  const Key* findSuccessor(const Key& k) const {
    Node* succ = successor(root, k);
    if (succ) return &succ->getKey();
    return nullptr; // no existe sucesor
  }

  const Key* findPredecessor(const Key& k) const {
    Node* pred = predecessor(root, k);
    if (pred) return &pred->getKey();
    return nullptr; // no existe predecesor
  }

private:
  Node* successor(Node* root, const Key& k) const {
    Node* succ = nullptr;
    Node* current = root;

    while (current != nullptr) {
      if (k < current->getKey()) {
        succ = current;           // posible sucesor
        current = current->getLeft();
      } else {
        current = current->getRight();
      }
    }
    return succ;
  }

  Node* predecessor(Node* root, const Key& k) const {
    Node* pred = nullptr;
    Node* current = root;

    while (current != nullptr) {
      if (current->getKey() < k) {
        pred = current;           // posible predecesor
        current = current->getRight();
      } else {
        current = current->getLeft();
      }
    }
    return pred;
  }

public:
  void remove(const Key &k) {
    root = remove(root, k);
  }

private:
  Node* remove(Node* node, const Key &k) {
    if (node == nullptr) return nullptr;

    if (k < node->getKey()) {
      node->setLeft(remove(node->getLeft(), k));
    } else if (node->getKey() < k) {
      node->setRight(remove(node->getRight(), k));
    } else {
      // Caso 1: nodo hoja
      if (!node->hasLeft() && !node->hasRight()) {
        delete node;
        sz--;
        return nullptr;
      }

      // Caso 2: un solo hijo
      if (!node->hasLeft()) {
        Node* rightChild = node->getRight();
        delete node;
        sz--;
        return rightChild;
      } else if (!node->hasRight()) {
        Node* leftChild = node->getLeft();
        delete node;
        sz--;
        return leftChild;
      }

      // Caso 3: dos hijos → usamos sucesor
      Node* succ = findMin(node->getRight());
      // copiamos key y value del sucesor
      node->setValue(succ->value);
      node->key = succ->getKey(); // acceso directo, ya que Node está dentro de BST
      // eliminamos el sucesor real
      node->setRight(remove(node->getRight(), succ->getKey()));
    }
    return node;
  }

public:
  void printTree() const {
    printTree(root, 0);
  }

private:
  void printTree(Node* node, int indent) const {
    if (node == nullptr) return;

    // primero el subárbol derecho
    printTree(node->getRight(), indent + 4);

    // imprime la sangría
    if (indent) {
      cout << setw(indent) << ' ';
    }

    // imprime la clave del nodo
    cout << node->getKey() << "\n";

    // luego el subárbol izquierdo
    printTree(node->getLeft(), indent + 4);
  }


};
#endif
