#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Define a room class to represent each location in the game world.
class Room {
    public:
        string description;
        map<string, int> exits;
        vector<string> items;

        Room(const string& desc) : description(desc) {}

        void AddExit(const string& direction, int roomIndex) {
            exits[direction] = roomIndex;
        }

        void AddItem(const string& item) {
            items.push_back(item);
        }
};

// define the game class to manage the game logic
class Game {
    public:
        vector<Room> rooms;
        int currentRoom;

        Game() : currentRoom(0) {}

        void InitializeGame() {
            // Create room and set their properties
            Room room1("You are in a small room. There is a door to the north.");
            room1.AddExit("north", 1);
            room1.AddItem("key");

            Room room2("You are in a large hall. There are exits to the south and east.");
            room2.AddExit("south", 0);
            room2.AddExit("east", 2);
            room2.AddItem("sword");

            Room room3("You are in a dark cave. There is an exit to the west.");
            room3.AddExit("west", 1);

            // Add rooms to the game world
            rooms.push_back(room1);
            rooms.push_back(room2);
            rooms.push_back(room3);
        }

        void RunGame() {
            cout << "Welcom to the Text Adventure Game! \n";
            cout << "............................................\n\n";

            while(true) {
                // Print the current room description
                const Room& currentRoomObj = rooms[currentRoom];
                cout << currentRoomObj.description << "\n\n";

                // Check if there are any items in the room
                if (!currentRoomObj.items.empty()) {
                    cout << "You see the following items in the room: ";
                    for (const string& item : currentRoomObj.items) {
                        cout << item << " ";
                    }
                    cout << "\n";
                }
                
                // Prompt for player input
                string command;
                cout << "> ";
                getline(cin, command);

                // Process player input
                if (command == "quit") {
                    cout << "Thank you for playing. Goodbye!\n";
                    break;
                }
                else if (command == "look") {
                    // Reprint room description
                    continue;
                }
                else if (command.find("go ") == 0) {
                    // Handle movement commands
                    string direction = command.substr(3);
                    if (currentRoomObj.exits.count(direction) > 0) {
                        currentRoom = rooms[currentRoom].exits[direction];
                    }
                    else {
                        cout << "You cannot go that way. \n";
                    }
                }
                else if (command.find("take ") == 0) {
                    // Handle item pickup commands
                    string item = command.substr(5);
                    if (currentRoomObj.items.empty() || find(currentRoomObj.items.begin(), currentRoomObj.items.end(), item) == currentRoomObj.items.end()) {
                        cout << "There is no " << item << "in the room. \n";
                    }
                    else {
                        cout << "You take the " << item << "in the room. \n";
                        // Remove the item from the room
                        rooms[currentRoom].items.erase(remove(rooms[currentRoom].items.begin(), rooms[currentRoom].items.end(), item), rooms[currentRoom].items.end());
                    }
                }
                else {
                    cout << "Invalid command. /n";
                }
            }
        }
    };

int main() {
    Game game;
    game.InitializeGame();
    game.RunGame();

    return 0;
}