#include "listasestudio.hh"
#include <studio.h>

template <typename T> 
class Queue{
private:
    List<T> storage;

public:
    Queue(): storage() {}
    
    Queue(const Queue<T>& other): storage(other.storage){}
    
    ~Queue(){}

    void push(const T &e){return storage.push_back(e)};

    unsigned int size() const{return storage.size() };

    bool empty(){return storage.empty()};

    T &front() { return storage.front(); }
    const T &front() const { return storage.front(); }
    void pop() { storage.pop_front(); }
};

