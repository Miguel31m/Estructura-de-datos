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
    unsigned int sz;   

    unsigned int hash(int key) const {
        int random_salt = time(NULL);      
        return (key * random_salt) % m;    
    }

public:
    HashtableInt(unsigned int m_size): m(m_size), storage(m_size), sz(0) {}   

    void insert(int key, const string &value) {
        unsigned int index = hash(key) % m;

        for (auto it = storage[index].begin(); it != storage[index].end(); ++it) {
            if (it->first == key) {
                it->second = value; 
                return;
            }
        }
        storage[index].push_back(make_pair(key, value));
        sz++;   
    }

    string get(int key) {
        unsigned int index = hash(key) % m;

        
        for (auto it = storage[index].begin(); it != storage[index].end(); ++it) {
            if (it->first == key) {
                return it->second;
            }
        }

        return "";
    }
    
    unsigned int size() const {
        return sz;
    }
};

#endif // __HASHTABLE_INT_HH__
