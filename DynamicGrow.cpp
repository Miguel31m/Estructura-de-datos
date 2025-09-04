#include <iostream>
#include <vector>
using namespace std;      

int main()  {
    vector<int> u;
    for(int i=1; i<1000; i++) {
        u.push_back(i);
        cout << "Tamaño: " << u.size() << ", Capacidad: " << u.capacity() << endl;
    }
    return 0;
}