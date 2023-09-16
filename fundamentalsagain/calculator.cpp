#include <iostream>

using namespace std;

int main() {
    char operation;
    double num1, num2;

    cout << "Enter an operation (+, -, *, /): ";
    cin >> operation;

    cout << "Enter a number: ";
    cin >> num1 >> num2;

    switch (operation) {
        case '+':
            cout << num1 << " +  " << num2 << " = " << (num1 + num2) << endl;
            break;
        case '-':
            cout << num1 << " - " << num2 << " = " << (num1 - num2) << endl;
            break;
        case '*':
            cout << num1 << " * " << num2 << " = " << (num1 * num2) << endl;
            break;
        case '/':
            if (num1 != 0) {
                cout << num1 << " / " << num2 << " = " << (num1 / num2) << endl;
            } else {
                cout << "Error Division by zero is not allowed." << endl;
            }
            break;
        default:
            cout << "Invalid operation. Please enter an operator" << endl;
            break; 
    }
    return 0;
}