#ifndef __RBT_HH__
#define __RBT_HH__

#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

template <typename Key, typename Value>
class RBT {
private:
  enum Color { RED, BLACK };

  class Node {
  private:
    Key key;
    Value value;
    Node *left;
    Node *right;
    Node *parent;
    Color color;

  public:
    Node(const Key &k, const Value &v)
        : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr),
          color(RED) {}

    const Key &getKey() const { return key; }
    Value &getValue() { return value; }
    bool isRed() const { return color == RED; }
    bool isBlack() const { return color == BLACK; }
    void setColor(Color c) { color = c; }
    Color getColor() const { return color; }

    bool hasLeft() const { return left != nullptr; }
    bool hasRight() const { return right != nullptr; }

    Node *getLeft() const { return left; }
    Node *getRight() const { return right; }
    Node *getParent() const { return parent; }

    void setLeft(Node *n) {
      left = n;
      if (n) n->parent = this;
    }

    void setRight(Node *n) {
      right = n;
      if (n) n->parent = this;
    }

    void setValue(const Value &v) { value = v; }
    void setKey(const Key &k) { key = k; }
  };

private:
  Node *root;
  unsigned int sz;

public:
  RBT() : root(nullptr), sz(0) {}
  ~RBT() { clear(root); }

  bool empty() const { return root == nullptr; }
  unsigned int size() const { return sz; }

  // --------- INSERCIÓN PRINCIPAL ----------
  void insert(const Key &k, const Value &v) {
    Node *newNode = new Node(k, v);
    root = bstInsert(root, newNode);
    fixInsert(newNode);
    sz++;
  }

private:
  Node *bstInsert(Node *root, Node *node) {
    if (root == nullptr)
      return node;

    if (node->getKey() < root->getKey()) {
      root->setLeft(bstInsert(root->getLeft(), node));
    } else if (root->getKey() < node->getKey()) {
      root->setRight(bstInsert(root->getRight(), node));
    } else {
      root->setValue(node->getValue()); // actualiza si ya existe
    }
    return root;
  }

  // --------- ROTACIONES ----------
  void rotateLeft(Node *x) {
    Node *y = x->getRight();
    x->setRight(y->getLeft());

    if (x->getParent() == nullptr)
      root = y;
    else if (x == x->getParent()->getLeft())
      x->getParent()->setLeft(y);
    else
      x->getParent()->setRight(y);

    y->setLeft(x);
    y->setColor(x->getColor());
    x->setColor(RED);
  }

  void rotateRight(Node *y) {
    Node *x = y->getLeft();
    y->setLeft(x->getRight());

    if (y->getParent() == nullptr)
      root = x;
    else if (y == y->getParent()->getLeft())
      y->getParent()->setLeft(x);
    else
      y->getParent()->setRight(x);

    x->setRight(y);
    x->setColor(y->getColor());
    y->setColor(RED);
  }

  // --------- CORRECCIÓN DESPUÉS DE INSERTAR ----------
  void fixInsert(Node *z) {
    while (z != root && z->getParent()->isRed()) {
      Node *parent = z->getParent();
      Node *grandparent = parent->getParent();

      if (parent == grandparent->getLeft()) {
        Node *uncle = grandparent->getRight();

        // Caso 1: Tío rojo
        if (uncle && uncle->isRed()) {
          parent->setColor(BLACK);
          uncle->setColor(BLACK);
          grandparent->setColor(RED);
          z = grandparent;
        } else {
          // Caso 2: z es hijo derecho → rotación izquierda
          if (z == parent->getRight()) {
            z = parent;
            rotateLeft(z);
          }
          // Caso 3: z es hijo izquierdo → rotación derecha
          parent->setColor(BLACK);
          grandparent->setColor(RED);
          rotateRight(grandparent);
        }
      } else {
        Node *uncle = grandparent->getLeft();

        // Caso 1 simétrico
        if (uncle && uncle->isRed()) {
          parent->setColor(BLACK);
          uncle->setColor(BLACK);
          grandparent->setColor(RED);
          z = grandparent;
        } else {
          // Caso 2 simétrico
          if (z == parent->getLeft()) {
            z = parent;
            rotateRight(z);
          }
          parent->setColor(BLACK);
          grandparent->setColor(RED);
          rotateLeft(grandparent);
        }
      }
    }
    root->setColor(BLACK);
  }

  void clear(Node *node) {
    if (!node) return;
    clear(node->getLeft());
    clear(node->getRight());
    delete node;
  }

  // --------- IMPRESIÓN ----------
public:
  void inorder() const { inorder(root); cout << endl; }
  void preorder() const { preorder(root); cout << endl; }
  void postorder() const { postorder(root); cout << endl; }

  void printTree() const { printTree(root, 0); }

private:
  void inorder(Node *node) const {
    if (!node) return;
    inorder(node->getLeft());
    cout << node->getKey() << (node->isRed() ? "(R) " : "(B) ");
    inorder(node->getRight());
  }

  void preorder(Node *node) const {
    if (!node) return;
    cout << node->getKey() << (node->isRed() ? "(R) " : "(B) ");
    preorder(node->getLeft());
    preorder(node->getRight());
  }

  void postorder(Node *node) const {
    if (!node) return;
    postorder(node->getLeft());
    postorder(node->getRight());
    cout << node->getKey() << (node->isRed() ? "(R) " : "(B) ");
  }

  void printTree(Node *node, int indent) const {
    if (!node) return;

    printTree(node->getRight(), indent + 6);
    if (indent) cout << setw(indent) << ' ';
    cout << node->getKey() << (node->isRed() ? " (R)\n" : " (B)\n");
    printTree(node->getLeft(), indent + 6);
  }
};

#endif
