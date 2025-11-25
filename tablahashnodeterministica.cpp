#include <thread>
#include <chrono>
#include <string>
#include "hashtablenodeterministica.hh"
#include <iostream>
using namespace std;

int main() {
    HashtableInt test(10);
    test.insert(10, "Hola");
    test.insert(12, "Mundo");
    this_thread::sleep_for(chrono::seconds(1));
    string s = test.get(10);
    cout << s << endl;
    this_thread::sleep_for(chrono::seconds(1));
    string t = test.get(12);
    cout << t << endl;
    return 0;
}
