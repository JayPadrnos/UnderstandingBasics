#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int target = rand() % 10 + 1;
    int guess;
    int lives = 4;

    cout << "Welcome to the number guessing game.\n";
    cout << "Guess any number between 1 and 10.\n";
    cout << "You have " << lives << " lives.\n";

    while (lives > 0) {
        cout << "Enter your guess: ";
        cin >> guess;

        if (guess == target) {
            cout << "Correct, you win! \n";
            return 0;
        } else {
            --lives;
            if (lives > 0) {
                cout << "Sorry, " << guess << " was not the right number, guess again. \n";
                cout << "You have " << lives << "lives left.\n";
            } else {
                cout << "Sorry, " << guess << "was not the right number and you have run out of lives! Game over.\n";
                return 0;
            }
        }
    }

    return 0;
}