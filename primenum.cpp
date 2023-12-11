#include <iostream>

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }

    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int num;
    std::cout << "Enter a number; ";
    std::cin >> num;

    if (isPrime(num)) {
        std::cout << num << " is prime." << std::endl;
    } else {
        std::cout << num << " is not prime." << std::endl;
    }

    return 0;
}