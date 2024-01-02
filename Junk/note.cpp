#include <iostream>
#include <vector>
#include <ctime>

using namespace std;


class Dice {
    public:
    Dice() {
        srand(static_cast<unsigned int>(time(0)));
    }

    int roll(int sides) {
        return rand() % sides + 1;
    }
};

int main() {
    Dice dice;
    int result = 0; 

    while (true) {
        cout << "Choose the number of sides for your dice. enter 0 to quit";
        int sides;
        cin >> sides;

        if (sides == 0) {
            cout << "Goodbye" << endl;
            break;
        }

        if (sides < 4 || sides % 2 !=0) {
            cout << "Invalid number of sides, Please choose again." << result << endl;
            continue;
        }

        result = dice.roll(sides);
        cout << "You rolled a D" << sides << " and got: " << result << endl;

        cout << "Do you want to roll again 1 for yes and 0 for no): ";
        int rollAgain;
        cin >> rollAgain;

        if (rollAgain == 0) {
            cout << "Goodbye" << endl;
            break;
        }
    }

    return 0;
}

// make play again functionable re ask the question and fix it proper as the code you were provided takes out current code
