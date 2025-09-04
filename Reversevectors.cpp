#include <iostream>
#include <vector>
using namespace std;

vector<int> reverseVector(const vector<int>& v) {
    vector<int> reversedvector;
    for (int i = v.size() - 1; i >= 0; --i) {
        reversedvector.push_back(v[i]);
    }
    return reversedvector;
}

int main() {
    vector<int> valores = {5, 6, 2, 3, 5};
    vector<int> invertido = reverseVector(valores);
    cout << "El vector invertido es: ";
    for (int elem : invertido) {
        cout << elem << " ";
    }
    cout << endl;
    return 0;
}