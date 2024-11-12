#include <iostream>

using namespace std;

int main() {
    int n;
    cout << "Enter a non-negative interger: ";
    cin >> n;

    // calculate factorial of n
    // write code here

    int factorial = 1; // initializes factorial to 1

    // calculate factorial of n
    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }



    cout << "The factorial of "<< n << " is: " << factorial << endl;

    return 0;
}