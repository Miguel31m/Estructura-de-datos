#include <iostream>
#include <vector>
using namespace std;

vector<int> mergeSorted(const vector<int>& a, const vector<int>& b) {
    vector<int> vectorordenado;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) {
            vectorordenado.push_back(a[i]);
            i++;
        } else {
            vectorordenado.push_back(b[j]);
            j++;
        }
    }
    
    while (i < a.size()) {
        vectorordenado.push_back(a[i]);
        i++;
    }
    while (j < b.size()) {
        vectorordenado.push_back(b[j]);
        j++;
    }
    return vectorordenado;
}

int main() {
    vector<int> a = {1, 3, 5, 7};
    vector<int> b = {2, 4, 6, 8};
    vector<int> ordenado = mergeSorted(a, b);
    cout << "El vector ordenado es: ";
    for (int elem : ordenado) {
        cout << elem << " ";
    }
    cout << endl;
    return 0;
}