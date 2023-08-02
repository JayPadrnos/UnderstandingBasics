#include <iostream>
using namespace std;

int main() {
    int x = 10; // Declares a normal variable

    int* ptr = &x; /* Declare a pointer variable and asssign it to the adress of x */

    cout << "Value of x: " << x << endl;
            // outputs: value of x: 10
    cout << "Address of x: " << &x << endl;
            // outputs: address of x: 0x9ad9dff654
                    // (value will vary)
    cout << "Value of ptr: " << ptr << endl;
            // outputs: value of ptr: 0x9ad9dff654
    cout << "Value of *ptr: " << *ptr << endl;
            // outputs: value of *ptr: 10

    return 0;
}