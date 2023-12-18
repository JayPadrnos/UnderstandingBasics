#include <iostream>

int main() {
    char operation;
    double num1, num2;

    while (true) {
        std::cout << "Choose an operation (+, -, *, /) or 'q' to quit: ";
        std::cin >> operation;

        if (operation == 'q') {
            std::cout << "Exiting calculator." << std::endl;
            break;
        }

        std::cout << "Enter two numbers: ";
        std::cin >> num1 >> num2;

        switch (operation) {
            case '+':
                std::cout << "Result: " << num1 + num2 << std::endl;
                break;
            case '-':
                std::cout << "Result: " << num1 - num2 << std::endl;
                break;
            case '*':
                std::cout << "Result: " << num1 * num2 << std::endl;
                break;
            case '/':
                if (num2 != 0) {
                    std::cout << "Result: " << num1 / num2 << std::endl;
                } else {
                    std::cout << "Error: Division by zero" << std::endl;
                }
                break;
            default:
                std::cout << "Invalid operation" << std::endl;
        }
    }

    return 0;
}