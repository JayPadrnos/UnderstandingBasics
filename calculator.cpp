#include <iostream>
using namespace std;

int main() {
    int num1, num2;
    char operation;

    cout << "Enter your first number: ";
    cin >> num1;

    cout << "Enter an operator (+, -, *, /): ";
    cin >> operation;

    cout << "Enter second number: ";
    cin >> num2; 

    if (operation == '+') {
        cout << "The result is: " << num1 + num2 << endl;
    } else if (operation == '-') {
        cout << "The result is: " << num1 - num2 << endl;
    } else if (operation == '*') {
        cout << "the result is: " << num1 * num2 << endl;
    } else if (operation == '/') {
        if(num2 != 0){
            cout << "The result is: " << num1 / num2 << endl;
      } else {
            cout << "Error! Dividing by zero is not allowed" << endl;
      }
    } else {
        cout << "Error! Invalid Operator." << endl;
    }

    return 0;
}