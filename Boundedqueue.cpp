#ifndef __BOUNDED__
#define __BOUNDED__
#include "listasestudio.hh"
#include <iostream>

template<typename T> class Boundedqueue{
private:
    List<T> storage;
    unsigned int capacity;
public:
    Boundedqueue(unsigned int cap): storage() , capacity(cap){}

    ~BoundedQueue() {}

    bool full(){ return storage.size()==capacity}

    void push(const T& e){
        if(full()){
            throw out_of_range("Capacidad maxima");

        }else{
            push_back(e);
        }
    }
    void pop(){ storage.pop_front(); }

    T& front(){ return storage.front(); }

    bool empty(){ return storage.empty(); }

    unsigned int size() const{ return storage.size(); }
    unsigned int max_size() const{ return capacity; }

}
