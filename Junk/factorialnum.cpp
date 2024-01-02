#include <iostream>
#include <algorithm>

int factorial(int n);

int main() {
    int num; 
    std::cout << "Enter a number";
    std::cin >> num;

    std::cout << "Factorial: " << factorial(num) << std::endl;

    return 0;
}

    // Factorial definition
    int factorial(int n) {
        if (n == 0 || n == 1) {
            return 1;
        } else {
            return n * factorial(n - 1);
        }
    }
