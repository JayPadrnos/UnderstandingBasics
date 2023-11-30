#include <iostream>
using namespace std;

int main() {
    double num1, num2; 

    cout << "Enter your first number";
    cin >> num1;

    cout << "Enter your second number";
    cin >> num2;

    double maxNumber = (num1 > num2) ? num1 : num2;

    cout << "Maximum: " << maxNumber << endl;

    return 0;
}