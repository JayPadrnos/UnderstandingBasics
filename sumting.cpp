#include <iostream>
#include <string>
#include <vector>

using namespace std;

int num1;
int num2;
int choice;

int main() {
    cout << "choose a number" << endl;
    cin >> num1;

    cout << "choose another number" << endl;
    cin >> num2;

    cout << "what operater would you like to choose";
    cin >> choice;

    switch (choice) {
        case '+' :
            cout << num1 << choice << num2 << " = " << answer << "\n";
            break;
    // make display to state which number is bigger than the other
    }
}