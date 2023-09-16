#include <iostream>
#include <cstdlib> // For random number gen
#include <ctime> // for seeding the rng
using namespace std;

class GuessingGame {
private:
    int secretNumber;
    int attemptsLeft;

public:
    GuessingGame(int min, int max, int attempts) {
        srand(time(nullptr)); // seed the rng
        secretNumber = rand() % (max - min + 1) + min;
        attemptsLeft = attempts;
    }

    void play() {
        cout << "Welcome to the Guess the number game" << endl;
        cout << "I'm thinking of a number between 1 and 100" << endl;

        while (attemptsLeft > 0) {
            int guess;
            cout << "You have " << attemptsLeft << " attempts left. enter your guess: ";
            cin >> guess;

            if (guess == secretNumber) {
                cout << "Congrats you win!" << endl;
                return;
            } else if (guess < secretNumber) {
                cout << "Too low. Try again." << endl;
            } else {
                cout << "Too high try again. " << endl;
            }

            attemptsLeft--;
        }

        cout << "Sorry youve run out of attempts the correct number was: " << secretNumber << endl;
    }
};

int main() {
    int minRange = 1;
    int maxRange = 100;
    int maxAttempts = 10;

    GuessingGame game(minRange, maxRange, maxAttempts);
    game.play();

    return 0;
}