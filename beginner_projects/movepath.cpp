#include <iostream>
using namespace std;

int main() {
    int currentRoom = 1; // starting room

    while (true) {
        // Display current room
        cout << "You are in a room " << currentRoom << endl;

        // Display available options
        cout << "Options ";
        cout << " 1 go to room 1 ";
        cout << " 2 go to room 2 ";
        cout << " 3 go to room 3 ";
        cout << " 0 Quit ";

        // Get user input
        int choice;
        cout << "Enter your choice. ";
        cin >> choice;

        // Process user input 
        switch (choice) {
            case 0:
                // Exit program 
                cout << "Goodbye!";
                return 0;
            case 1:
                currentRoom = 1;
                break;
            case 2:
                currentRoom = 2;
                break;
            case 3:
                currentRoom = 3;
                break;
            default:
                cout <<  "Invalid choice. Please try again.";
                break;
            }
        }

    return 0;
}

// get it so you can use it in the other program so that you cant go from room 4 to room 1 unless they are connected and if they cant be sure to have an else for that and msg printed\
// also see if you cant get it printed to terminal like tic tac toe so that the player can get a map and see it in terminal
