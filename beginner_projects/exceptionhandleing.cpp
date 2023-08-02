#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int b = 0;
    int c;

    try {
        if(b == 0)
            throw "Division by zero error";
             //throw an error
        else
        c = a/b; // performs division if no error
    } catch (const char* e) {
        cout << "Exception: " << e << endl;
            // Catch and handle the error
    }
    return 0;
}