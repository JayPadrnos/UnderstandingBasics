#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>

int main() {
    srand(static_cast<unsigned int>(time(0))); // seed random number generator

    int target = rand() % 10 + 1;
        // Generate target number: a random integer between 1 and 10
    int guess; //Variable to hold user's guess
    int lives = 4; // user starts with 4 lives

    cout << "Welcome to the Number Guessing Game.\n";
    cout << "Guess any number between 1 and 10\n";
    cout << "You have " << lives << " lives.\n";

    while (lives > 0) {
        cout << "Enter your guess: ";
        cin >> guess;

        if (guess == target) {
            cout << "Correct, you win! \n";
            return 0; // End the game if the user guessed correctly.
        } else {
            --lives; // Decrement the user's lives
            if (lives > 0) {
                cout << "Sorry, " << guess << " was not the right number, guess again.\n";
                cout << "You have " << lives << " lives left.\n";
            } else {
                cout << "Sorry, " << guess << "was not the right number and you have run out of lives! Game Over!\n";
                return 0; // End the game if the user has run out of lives.
            }
        }
    }

    return 0;
}