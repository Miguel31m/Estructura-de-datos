#include <iostream>
using namespace std;

template<typename T> class List{
private:
    class Node{
    private:
        T data;
        Node *next;
    public:
        Node():data(),next(nullptr) {}
        Node(const T& v) : data(v), next(nullptr) {}
        Node* getNext() const { return next; }
        void setNext(Node *n) { next = n; }
    
    };
    Node* first;
    Node* last;
    unsigned int sz;
public:
    
    List() : first(nullptr), last(nullptr), sz(0) {}
    
    ~List() {
    Node *temp = first;
    while (first != nullptr) {
      temp = first;
      first = first->getNext();
      delete temp;
    }
    last = nullptr;
    sz = 0;
  }
  
  bool empty() const { 
    return first == nullptr && last == nullptr;
  }

  void push_back(const T& elem){
    Node* new_node=new Node(elem);
    if(!empty()){
      last->setNext(new_node);
      last=new_node;
    }else{
      first=new_node;
      last=new_node;
    }
    sz++;
  }

  void pop_back(){
    if(empty()){ return;}

    if(first==last){
      first=nullptr;
      last=nullptr;
    }
    if(!empty()){
      Node* temp=nullptr;
      Node* actual=first;
      while(actual->getNext()!=nullptr){
        temp=actual;
        actual=actual->getNext();
      }
      delete actual;
      temp->setNext(nullptr);
      last=temp;
    }
    sz--;
    
  }
  void push_front( const T& val) {
    Node* nuevo=new Node(val);
    nuevo->setNext(first);
    first=nuevo;
    if(last == nullptr){  
        last = nuevo;
    }

    sz++;
  }
  void pop_front() {
    
    if(empty()){return;}
    Node* temp=first->getNext();
    delete first;
    first=temp;

    if(first==last){
      last=nullptr;
    }
    sz--;
  }

  T& front() { 
    
    if(empty()){
      throw out_of_range("La lista esta vacia");
    }
    return first->data;
  }
  const T& front() const {
    if(empty()){
      throw out_of_range("La lista esta vacia");
    }
    return first->data;
  }

  T& back() {
    if(empty()){
      throw out_of_range("La lista esta vacia");
    }
    return last->data;
  }
   const T& back() const {
    if(empty()){
      throw out_of_range("La lista esta vacia");
    }
    return last->data;
  }

  unsigned int size() const {
    return sz;
  }
  void clear() {
    Node *temp=first;
    while(first->getNext()!=nullptr){
      temp=first;
      first=first->getNext();
      delete temp;
    }
    last=nullptr;
    sz--;
  }
  const T& at(unsigned int index) const {
    if(index>=sz){
      throw out_of_range("Posicion invalida");

    }
    Node* temp=first;
    for(unsigned int i=0;i<index;i++){
        temp=temp->getNext();
    }
    return temp->data;
  }

  T& at(unsigned int index) {
    if(index>=sz){
      throw out_of_range("Posicion invalida");

    }
    Node* temp=first;
    for(unsigned int i=0;i<index;i++){
        temp=temp->getNext();
    }
    return temp->data
  }

  const T& operator[](unsigned int index) const {
    Node* temp=first;
    for(unsigned int i=0;i<index;i++){
        temp=temp->getNext();
    }
    return temp->data
  }

  T& operator[](unsigned int index) {
    Node* temp=first;
    for(unsigned int i=0;i<index;i++){
        temp=temp->getNext();
    }
    return temp->data
  }

  void insert(unsigned int index, const T& val) {
    if (index > sz) { 
        throw out_of_range("Fuera de limites");
    }

    if (index == 0) {
        push_front(val);
    } else if (index == sz) {
        push_back(val);
    } else {
        Node* nuevo = new Node(val);
        Node* temp = first;

        
        for (unsigned int i = 0; i < index - 1; i++) {
            temp = temp->getNext();
        }

        // insertar el nodo
        nuevo->setNext(temp->getNext());
        temp->setNext(nuevo);

        sz++;
      }

  }
  void erase(unsigned int index) {
    if (index > sz) { 
        throw out_of_range("Fuera de limites");
    }else if(index==sz-1){
      pop_back();
    }else if(index==0){
      pop_front();
    }else{
    
    Node* temp=first;
    for(unsigned int i=0;i<index-1;i++){
        temp=temp->getNext();
    }
    Node* despues=temp->getNext();
    temp->setNext(despues->getNext());
    delete despues;
    sz--;
    }
  }

  void print() const {
    Node *temp = first;
    while (temp != nullptr) {
      cout << temp->data << " ";
      temp = temp->getNext();
    }
    cout << endl; 
  }
  void reverse() {
    if(empty()||first==last){
      return;
    }
    Node* antes=nullptr;
    Node* actual= first;
    Node* despues=nullptr;
    last=first;
    while(actual!=nullptr){
      despues=actual->getNext();
      actual->setNext(antes);
      antes=actual;
      actual=despues;

    }
    first=antes;
  }
  List(const List &other) {
    sz = other.sz;
    first = nullptr;
    last = nullptr;

    if (other.first == nullptr) {
        return; 
    }

    
    first = new Node(other.first->data);
    last = first;

    Node* tempother = other.first->getNext();
    while (tempother != nullptr) {
        Node* nuevo = new Node(tempother->data);
        last->setNext(nuevo);
        last = nuevo;
        tempother = tempother->getNext();
    }
  }
  void push_back(const List &other) {
    Node* tempother = other.first;
    while (tempother != nullptr) {
        push_back(tempother->data);  
        tempother = tempother->getNext();
    }
  }
  void push_front(const List &other) {
    push_front_rec(other.first);
  }

  void push_front_rec(Node* nodo) {
    if (nodo == nullptr) return;
    // primero bajo hasta el último
    push_front_rec(nodo->getNext());
    // cuando vuelvo, inserto
    push_front(nodo->data);
  }

};