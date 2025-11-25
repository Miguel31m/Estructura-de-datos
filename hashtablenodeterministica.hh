#ifndef __HASHTABLE_INT_HH__
#define __HASHTABLE_INT_HH__

#include <vector>
#include <list>
#include <string>
#include <utility>
#include <ctime>


using namespace std;

class HashtableInt {
private:
    unsigned int m;
    vector<list<pair<int, string>>> storage;

    unsigned int hash(int key) const {
        int random_salt = time(NULL);      // NO determinística
        return (key * random_salt) % m;    // cambia cada segundo
    }

public:
    HashtableInt(unsigned int m_size)
        : m(m_size), storage(m_size) {}

    // ==============================
    //           INSERT
    // ==============================
    void insert(int key, const string &value) {
        unsigned int index = hash(key);

        // Revisar si ya existe la llave
        for (auto &elem : storage[index]) {
            if (elem.first == key) {
                elem.second = value;       // actualizar si ya existe
                return;
            }
        }

        // Si no existe, la agregamos a la lista
        storage[index].push_back(make_pair(key, value));
    }

    // ==============================
    //             GET
    // ==============================
    string get(int key) {
        unsigned int index = hash(key);

        // Recorrer la lista del bucket correspondiente
        for (auto &elem : storage[index]) {
            if (elem.first == key) {
                return elem.second;
            }
        }

        return "NOT FOUND";
    }
};

#endif // __HASHTABLE_INT_HH__
