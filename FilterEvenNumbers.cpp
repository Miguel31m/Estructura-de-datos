#include <iostream>
#include <vector>
using namespace std;

vector<int> filterEven(const vector<int>& v){
    vector<int> pares;
    for(int elem: v){
        if(elem % 2 == 0){
            pares.push_back(elem);
        }
    }
    return pares;
}

int main(){
    vector<int> valores={5,6,2,3,5};
    vector<int> pares=filterEven(valores);
    cout <<"Los numeros pares son: ";
    for(int elem: pares){
        cout << elem << " ";

    }
    return 0;
}