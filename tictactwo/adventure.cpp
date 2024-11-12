#include "adventure.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

Adventure::Adventure() : playerLife(3), hasSword(false), hasKey(false) {
    // Add any additional initialization code for the adventure class here
}

void Adventure::startGame() {
    // Get the start time of the game
    startTime = chrono::steady_clock::now();

    // Adventure game implementation
    // Create game logic rooms options etc
    // Make sure to keep it fast and simple for now

    cout << "Welcome to the Adventure of your choosing\n";
    cout << "You find yourself in a dark room, dimly lit by candle\n";

    // Main game loop
    while (playerLife > 0) {
        cout << "\nWhat would you like to do? \n";
        cout << "1. Look around.\n";
        cout << "2. Open a chest.\n";
        cout << "3. Walk through the next door. \n";
        cout << "4. Quit the game.\n";
        cout << "Make your decision.\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "You look around the room and find a sword.\n";
                cout << "You pick up the sword and notice your dirty face in the shiny blade.";
                hasSword = true;
                break;
            case 2:
                if (hasSword) {
                    cout << "You use the sword to open the chest. \n";
                    cout << "Inside the chest, you find a key.\n";
                    cout << "You take the key and notice it is cold to the touch.\n";
                    hasKey = true;
                } else {
                    cout << "The chest is locked. Maybe you need something to open it.\n";
                }
                    break;
            case 3:
                if (hasKey) {
                    cout << "You use the key to unlock the door. \n";
                    cout << "Congrats! You escaped the dungeon.\n";
                    cout << "You return to the main menu\n";
                } else {
                    cout << "The door is locked. You need a key to open it.\n";
                }
                    break;
            case 4:
                    cout << "You decide to quit the game.\n";
                    cout << "You return to the main menu.\n";
                    return;
            default:
                    cout << "Invalid choice. Please try again.\n";
        }
    }

    // If the player runs out of lives the game ends.
    cout << "Game Over. No more lives to continue.\n";
    cout << "You return to the main menu.\n";
}

string Adventure::getTimeDuration() {
    // Get the end time of the game
    endTime = chrono::steady_clock::now();

    // Calculate the duration of the game in seconds
    auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();

    // Convert the duration to a formatted string (HH:WW:SS)
    int hours = duration / 3600;
    int minutes = (duration % 3600) / 60;
    int seconds = duration % 60;
    return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
}