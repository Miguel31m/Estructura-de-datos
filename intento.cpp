#include <iostream>
#include "vector.hh"
#include <string> 

using namespace std;

bool esDigito(char &digito){
    return (digito>='0' && digito<='9')||digito==' ';
}

int sumacaracteres(Vector<string>& a){
    Vector<int> numeros;
    if(!esDigito()){throw out_of_range("No existe");
    }else{
        for(unsigned int i=0;i<a.size();i++){
            if(a[i]==' '){
                continue;
            }
            
        }
    }
}

int main(){
    string valor;
    cout<<"Ingrese el valor: "<<endl;
    cin>> valor;
}