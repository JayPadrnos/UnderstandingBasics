#include <iostream>

int main() {
    int num1, num2;
    char operation;

    std::cout << "Enter first number: ";
    std::cin >> num1;

    std::cout << "Enter an operator (+, -, *, /): ";
    std::cin >> operation;

    std::cout << "Enter second number: ";
    std::cin >> num2;

    if (operation == '+') {
        std::cout << "The result is: " << num1 + num2 << std::endl;
    } else if (operation == '-') {
        std::cout << "The result is: " << num1 - num2 << std::endl;
    } else if (operation == '*') {
        std::cout << "The result is: " << num1 * num2 << std::endl;
    } else if (operation == '/') {
        if(num2 != 0){
            std::cout << "The result is: " << num1 / num2 << std::endl;
        } else {
            std::cout << "Error! Division by zero is not allowed." << std::endl;
        }
    } else {
        std::cout << "Error! Invalid operator." << std::endl;
    }

    return 0;
}
