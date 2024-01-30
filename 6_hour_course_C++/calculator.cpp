#include <iostream>

int main() {

    char op;
    double num1;
    double num2;
    double result;

    std::cout << "******** CALCULATOR ***********\n";

    std::cout << "Enter either (+, -, *, /): ";
    std::cin >> op;

    std::cout << "Enter number 1: ";
    std::cin >> num1;

    std::cout << "Enter number 2: ";
    std::cin >> num2;

    switch(op){
        case '+':
            result = num1 + num2;
            std::cout << "Result: " << result << '\n';
            break;
        case '-':
            result = num1 - num2;
            std::cout << "Result: " << result << '\n';
            break;
        case '*':
            result = num1 * num2;
            std::cout << "Result: " << result << '\n';
            break;
        case '/':
            result = num1 / num2;
            std::cout << "Result: " << result << '\n';
            break;
        default:
            std::cout << "That wasn't a valid operator\n";
            break;
    }


    std::cout << "**********************************";

    return 0;
}