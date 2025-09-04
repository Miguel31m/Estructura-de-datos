#include <iostream>
#include <vector>
using namespace std;
int sumVector(const vector<int>& v){
    int suma=0;
    for(int elem: v){
        suma +=elem;
    }
    return suma;
}

int main(){
    vector<int> valores={5,6,2,3,5};
    cout <<"La suma de los valores es: "<<sumVector(valores)<<std::endl;
    return 0;
}