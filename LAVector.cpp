#include <iostream>
#include <math.h>
using namespace std;

class LAVector{
private:
    int *storage;
    unsigned int sz;

public:
    LAVector(){
        sz=3;
        storage= new int[3];
    }
    LAVector(unsigned int a=0, unsigned int b=0, unsigned int c=0){
        sz=3;
        storage= new int[3];
        storage[0]=a;
        storage[1]=b;
        storage[2]=c;
    }
    int size() const{return sz;}
    LAVector(const LAVector& other){
        sz=other.size();
        storage= new int[3];
        for(unsigned int i=0;i<other.size();i++){
            storage[i]=other.storage[i];
        }
     }

    ~LAVector() {
        delete[] storage;
    }
    int &operator[](unsigned int index){return storage[index];}
    int const &operator[](unsigned int index){return storage[index];}
    
};

LAVector sumavectores(const LAVector& a, const LAVector& b){
    LAVector  sumavectores;
    for(unsigned int i=0;i<3;i++){
        sumavectores[i]=a[i]+b[i];
    }
    return sumavectores;
}

LAVector restavectores(const LAVector& a, const LAVector& b){
    LAVector  restavectores;
    for(unsigned int i=0;i<3;i++){
        restavectores[i]=a[i]-b[i];
    }
    return restavectores;
}
LAVector multiplicacionescalar(const LAVector& a, int b){
    LAVector multiplicacionescalar;
    for(unsigned int i=0;i<3;i++){
        multiplicacionescalar[i]=b*a[i];
    }
    return multiplicacionescalar;
}

int dot_product(const LAVector& a, const LAVector& b){
    int suma=0;
    for(unsigned int i=0;i<3;i++){
        suma= suma+ (a[i]*b[i]);
    }
    return suma;
}
double magnitude(const LAVector& a){
    double suma=0;
    for(unsigned int i=0;i<3;i++){
        suma= suma+(a[i]*a[i]);
    }
    double total= sqrt(suma);
    return total;
    
}
LAVector normalize(const LAVector& a){
    double mag = magnitude(a);
    LAVector resultado;
    for(unsigned int i=0; i<a.size(); i++)
        resultado[i] = a[i] / mag;
    return resultado;
}

