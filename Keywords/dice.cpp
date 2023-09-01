#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
// Funtion to roll a d20 dice and return the result
int rollDice() {
    return rand() % 20 + 1;
}

//Funtion to perform an attack action 
bool performAttack(int attackBonus) {
    int roll = rollDice();
    int totalAttack = roll + attackBonus;

    cout << "Your rolled a " << roll << " (+" << attackBonus << "attack bonus)";

    if (totalAttack >= 15) {
        cout << "Success! you hit the target.";
        return true;
    } else {
        cout << "You missed your target.";
        return false;
    }
}

int main() {
    // Seed the random number gen with current time
    srand(static_cast<unsigned>(time(0)));

    // Character attributes
    int attackBonus = 3;

    // Game loop
    while (true) {
        char input;
        cout << "It's your turn. enter 'a' to attack or q to quit.";
        cin >> input;

        if (input == 'q') {
            cout << "Existing the game. Goodbye!";
            break;
        } else if (input == 'a') {
                if (performAttack(attackBonus)) {
                    // Handle successful attacks eg reduce enemy health
                } else {
                    // Handle missed attack
            }
        } else {
            cout << "Invalid input, try again.";
        }
    }

    return 0;
}