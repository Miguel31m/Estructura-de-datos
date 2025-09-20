#include <iostream>

using namespace std;

template <typename T> class Vector {
private:
  // Stores the elements of the vector
  T *storage;
  
  // Current number of elements in the vector
  unsigned int sz;
  
  // Maximum number of elements that storage can hold
  unsigned int capacity;
  
  // Policy for resizing the vector
  double policy;

public:
  Vector() {
    storage = new T[5];
    sz = 0;
    capacity = 5;
    policy = 1.5;
  }

  Vector(unsigned int c, double p = 1.5) {
    storage = new T[c];   
    sz = 0;
    capacity = c;
    policy = p;
  }

  Vector(const Vector<T> &other) {
    sz = other.size();
    capacity = other.capacity;
    policy = other.policy;
    storage = new T[capacity];
    for (unsigned int i = 0; i < sz; i++) {
      storage[i] = other.storage[i];
    }
  }

  ~Vector() { delete[] storage; }

  void push_back(const T &elem) {
    if (sz == capacity) {
      resize();
    }
    storage[sz] = elem;
    sz++;
  }

  void push_back(const Vector<T> &other) {
    reserve(sz + other.size());
    for (unsigned int i = 0; i < other.size(); i++) {
      push_back(other.storage[i]);
    }
  }

  void pop_back() { sz--; }

  unsigned int size() const { return sz; }
  unsigned int capacity() const { return capacity;}

private:
  void resize() {
    capacity *= policy;
    T *new_storage = new T[capacity];
    for (unsigned int i = 0; i < sz; i++) {
      new_storage[i] = storage[i];
    }
    delete[] storage;
    storage = new_storage;
  }

  void reserve(unsigned int new_capacity) {
    if (new_capacity > capacity) {
      capacity = new_capacity;
      T *new_storage = new T[capacity];
      for (unsigned int i = 0; i < sz; i++) {
        new_storage[i] = storage[i];
      }
      delete[] storage;
      storage = new_storage;
    }
  }

public:
  void shrink_to_fit() {
    if (sz < capacity) {
      T *new_storage = new T[sz];
      for (unsigned int i = 0; i < sz; i++) {
        new_storage[i] = storage[i];
      }
      delete[] storage;
      storage = new_storage;
      capacity = sz;
    }
  }

  T &operator[](unsigned int index) { return storage[index]; }

  const T &operator[](unsigned int index) const { return storage[index]; }

  T &at(unsigned int index) {
    if (index >= sz) {
      throw out_of_range("Index out of range");
    }
    return storage[index];
  }

  const T &at(unsigned int index) const {
    if (index >= sz) {
      throw out_of_range("Index out of range");
    }
    return storage[index];
  }

  bool empty() const { return sz == 0; }
};

int SumaVector(const Vector<int>& v){
    int suma=0;
    for(int i=0;i<v.size();i++){
        suma= suma+v.at(i);
    }
    return suma;
}

Vector <int> reversevector(const Vector<int>& v){
    Vector <int> vectoreversa(v.size());
    for(int i=v.size()-1;i>-1;i--){

        vectoreversa.push_back(v[i]);
    }
    return vectoreversa;
}

Vector <int> FilterEvenNumbers(const Vector<int>& v){
    Vector <int> vectorfiltrado(v.size());
    for(int i=0;i<v.size();i++){
        if(v[i]%2==0){
            vectorfiltrado.push_back(v[i]);
        }
    }
    vectorfiltrado.shrink_to_fit();
    return vectorfiltrado;
}

void DynamicGrowthTest(){
    Vector <int> u;
    unsigned int capacidadprevia=u.capacity();
    for(int i=0;i<1001;i++){
        u.push_back(i);
        if(u.capacity()!=capacidadprevia){
            cout<<"Size: "<<u.size()<<"  Capacity: "<<u.capacity()<<endl;
            capacidadprevia=u.capacity();
        }
    }
}

Vector<int> mergeSorted(const Vector<int>& a, const Vector<int>& b) {
    Vector<int> copia(a.size() + b.size());  // capacidad suficiente
    int i = 0, j = 0;

    // Recorremos ambos mientras tengan elementos
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) {
            copia.push_back(a[i]);
            i++;
        } else {
            copia.push_back(b[j]);
            j++;
        }
    }

    // Si aún quedan elementos en 'a', los agregamos
    while (i < a.size()) {
        copia.push_back(a[i]);
        i++;
    }

    // Si aún quedan elementos en 'b', los agregamos
    while (j < b.size()) {
        copia.push_back(b[j]);
        j++;
    }

    copia.shrink_to_fit(); // opcional, ajusta la memoria al tamaño final
    return copia;
}