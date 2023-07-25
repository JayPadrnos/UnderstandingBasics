#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "tictactwo.hpp"

using namespace std;


void mainMenu();

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    cout << "Welcome to the Game Hub!\n";
    int choice;

    while (true) {
        cout << "\nMain Menu:\n";
        cout << "1. Tic Tac Toe\n";
        cout << "2. Game 2\n";
        cout << "3. Game 3\n";
        // Add additional games as you complete the current program
        cout << "4. Exit\n";
        cout << "So what would you like to play?";
        cin >> choice;

        switch (choice) {
            case 1: {
                TicTacToe ticTacToe;
                bool playAgain = true;

                while (playAgain) {
                    ticTacToe.playGame();

                    // Ask the player if they want to play again
                    char playAgainChoice;
                    cout << "Do you want to play again> (y/n): ";
                    cin >> playAgainChoice;
                    if (playAgainChoice != 'y' && playAgainChoice != 'Y') {
                        playAgain = false;
                    }
                }
                        ticTacToe.displayMatchHistory();
                        break;
            }
                case 2:
                    // Cell game2() function here
                    cout << "Game 2 Under construction. Come back later to see if its complete";
                    break;
                case 3:
                    // Cell game3() function here
                    cout << "If game two was under construction why did you think Game 3 would be ready?";
                    break;
                case 4:
                cout << "Goodbye thanks for playing";
                    return;
                default:
                cout << "Invalid choice. Please try again \n";
        }
    }
}