// have user input numbers only for system to say if it is even or odd.

#include <iostream>

int main() {
    // Declare variables
    double userNumber;

    // Take user input 
    std::cout << "Enter a number: " ;
    std::cin >> userNumber;

    // Check if the number is whole
    if (userNumber ==
    static_cast<int>(userNumber)) {
        // Check if the number is odd or even
        if (static_cast<int>(userNumber) % 2 == 0) {
            std::cout << "The number is even." << std::endl;
        } else {
            std::cout << "The number is odd" << std::endl;
        }
    } else {
        std::cout << "The entered number is not a whole number." << std::endl;
    }

    return 0;
}