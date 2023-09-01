#include "diceroll.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int DiceGame::rollDice(int sides) {
    return rand() % sides + 1; // Generate a random number between 1 and sides
}

bool DiceGame::playAgain() {
    string response;
    cout << "Do you want to roll again?";
    cin >> response;
    return (response == "yes" || response == "y");
}

void DiceGame::play() {
    srand(time(nullptr)); // Seed the random number generator with current time

    cout << "Welcome to the Dice Rolling simulator";

    int sides;
    do {
        cout << "Choose the type of dice to roll (4, 6, 8, 10, 12, 20): ";
        cin >> sides;

        if (sides == 4 || sides == 6 || sides == 8 || sides == 10 || sides == 12 || sides == 20) {
            int result = rollDice(sides);
            cout << "You rolled a " << result << "!\n";
        } else {
            cout << "Invalid dice type. Please choose from the available options";
        }
    } while (playAgain());
}