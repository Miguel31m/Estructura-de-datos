#ifndef __HASHTABLE_LP_HH__
#define __HASHTABLE_LP_HH__

#include <vector>
#include <utility>
#include <string>

using namespace std;

template <typename K, typename V>
class HashtableLP {
private:
    unsigned int m;
    vector<pair<K, V>> storage;
    vector<bool> used; // para saber si una celda está ocupada

    unsigned int hash(const K &key) const {
        return std::hash<K>{}(key) % m;
    }

public:
    HashtableLP(unsigned int size)
        : m(size), storage(size), used(size, false) {}

    // ==============================
    //            INSERT
    // ==============================
    void insert(const K &key, const V &value) {
        unsigned int index = hash(key);

        for (unsigned int i = 0; i < m; i++) {
            unsigned int probe = (index + i) % m;

            if (!used[probe]) {
                storage[probe] = make_pair(key, value);
                used[probe] = true;
                return;
            }
        }

        throw runtime_error("Tabla hash llena");
    }

    // ==============================
    //            FIND
    // ==============================
    V find(const K &key) const {
        unsigned int index = hash(key);

        for (unsigned int i = 0; i < m; i++) {
            unsigned int probe = (index + i) % m;

            if (!used[probe])
                return "NOT FOUND";

            if (used[probe] && storage[probe].first == key)
                return storage[probe].second;
        }

        return "NOT FOUND";
    }

    // ==============================
    //           REMOVE
    // ==============================
    void remove(const K &key) {
        unsigned int index = hash(key);

        for (unsigned int i = 0; i < m; i++) {
            unsigned int probe = (index + i) % m;

            if (!used[probe])
                return;

            if (storage[probe].first == key) {
                used[probe] = false;
                return;
            }
        }
    }
};

#endif
