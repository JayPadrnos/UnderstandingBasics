#include <iostream>
using namespace std;

int main() {
    int x = 10; // a normal integer
    int& ref = x; // a reference to x

    cout << "x: " << x << endl; // outputs: x: 10
    cout << "ref: " << ref << endl; // outputs: ref: 10

    ref = 20; // change the value of x through the reference
    cout <<  "x: " << x << endl; // outputs: x: 20
    cout << "ref: " << ref << endl; // outputs: ref: 20

    return 0;
}