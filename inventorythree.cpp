#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Room {
    string description;
    vector<int> exits;
    vector<int> items;
    bool hasEnemy;
    bool hasLever;
};

struct Item {
    int id;
    string name;
    string description;
};

struct Player {
    string name;
    string playerClass;
    string description;

};

struct Enemy {
    string name;
    int attack;
    int defense;
    int health;
};

// Game world data
vector<Room> rooms;
vector<Item> items;
vector<Enemy> enemies;

// Initialize rooms
void initializeRooms() {
    Room room1;
    room1.description = "You are in a dimly lit room";
    room1.exits = {1}; // Room 1 connects to room 2
    room1.items = {1}; // Room 1 has item with ID 1
    room1.hasEnemy = false;
    rooms.push_back(room1);

    Room room2;
    room2.description = "You are in a hallway with torches lit.";
    room2.exits = {0, 2}; // Room 2 connects to room 1 and room 3
    room2.items = {}; // Room 2 has no items
    room2.hasEnemy = true;
    rooms.push_back(room2);

    Room room3;
    room3.description = "You have entered a large dome like room, you can see two large doors on the other sides of the room.";
    room3.exits = {2, 4, 5}; // Room 3 connects to room 2, 4, and 5
    room3.items = {2}; // Room 3 has 1 item with ID 2
    room3.hasEnemy = false;
    rooms.push_back(room3);

    Room room4;
    room4.exits = {3};
    room4.items = {3, 4};
    room4.hasEnemy = true;
    rooms.push_back(room4);

    Room room5;
    room5.exits = {3, 6};
    room5.items = {};
    room5.hasEnemy = false;
    rooms.push_back(room5);

    Room room6;
    room6.exits = {5};
    room6.items = {5};
    room6.hasEnemy = true;
    rooms.push_back(room6);

    //! Fix how the rooms are traversed they need spaces in the cout at the end on top of needing options that are not 0 - 3 need a way to better choose options in the rooms once the description of room is told to user
    // Be sure you can traverse the rooms, See what is in the room, then decide on what to do based off of what the player sees
    // Make a perception check for the players stat so that they may not be able to choose or even see options for rooms based off the check
    // Have a lever in room 1 that needs a key or a piece of the lever so that it opens room7 leading to a "Boss" fight
}

// Initialize items
void initializeItems() {
    Item item1;
    item1.id = 1;
    item1.name = "Sword";
    item1.description = "A sharp sword.";
    items.push_back(item1);

    Item item2;
    item2.id = 2;
    item2.name = "Schimitar";
    item2.description = "A broad curved blade";
    items.push_back(item2);

    Item item3;
    item3.id = 3;
    item3.name = "Wood Armor";
    item3.description = "Simple wooden armor";
    items.push_back(item3);

    Item item4;
    item4.id = 4;
    item4.name = "Rusty Key";
    item4.description = "A key for a a door, the key looks to be rusted.";
    items.push_back(item4);

    Item item5;
    item5.id = 5;
    item5.name = "Metal Armor";
    item5.description = "Heavy Armor made from scrap metals";
    items.push_back(item5);

    // Add more rooms so that you can add more items and creatures.
    /// Make locks capable to be unlocked by keys so that the "Rusty Key" and other key items can unlock doors.
    // Find a way that the player can be awarded these items after fighting the enemies vs just finding them for entering the room. 



}

// Initialize enemies
void initializeEnemies() {
    Enemy enemy1;
    enemy1.name = "Skeleton";
    enemy1.attack = 10;
    enemy1.defense = 5;
    enemy1.health = 20;
    enemies.push_back(enemy1);

    Enemy enemy2;
    enemy2.name = "Zombie";
    enemy2.attack = 20;
    enemy2.defense = 10;
    enemy2.health = 30;
    enemies.push_back(enemy2);

    Enemy enemy3;
    enemy3.name = "Vampire";
    enemy3.attack = 15;
    enemy3.defense = 5;
    enemy3.health = 50;
    enemies.push_back(enemy3);

    // Have a "Boss" that can have multiple phases of the fight
    // Figure out how to put the enemies in the specific room
    // Allow for multiple enemies in the same room
}

// Initialize the game world
void initializeGameWorld() {
    initializeRooms();
    initializeItems();
    initializeEnemies();
}

int currentRoomIndex = 0; // Index of the current room the player is in
vector<int> playerInventory; // Player's inventory to hold item IDs

// Function to handle player movement
void movePlayer(int direction) {
    if (direction >= 0 && direction < rooms[currentRoomIndex].exits.size()) {
        currentRoomIndex = rooms[currentRoomIndex].exits[direction];
        cout << rooms[currentRoomIndex].description;

        // Check for enemy encounter
        if (rooms[currentRoomIndex].hasEnemy) {
            cout << "An enemy has appeared";
            // Handle enemy encounter logic
            //.....
            bool suprise;
            if (suprise = true) {
                    // Find if correct for a bool to get a suprised bonuse for player attack, the effect should be stated after the enemies description.
        }
    } else {
        cout << "Cannot go in that direction";
        }
    }
}


// Function to handle picking up an item
void pickUpItem(int itemId) {
    Room& currentRoom = rooms[currentRoomIndex];
    auto it = find(currentRoom.items.begin(), currentRoom.items.end(), itemId);
    if (it != currentRoom.items.end()) {
        playerInventory.push_back(itemId);
        currentRoom.items.erase(it);
        cout << "Picked up item: " << items[itemId].name;
    } else {
        cout << "No such item in the room. ";
    }
}

// Function to handle using an item
void useItem(int itemId) {
    // Implement item usage logic based on item ID and game requirements
    // .....
}

void displayGameWorld() {
    // Clear the console
    system("clear");

    // Draw the game world grid
    for (int i = 0; i < rooms.size(); ++i) {
        if (i == currentRoomIndex) {
            cout << "O"; // Players position
        } else if (rooms[i].hasEnemy) {
            cout << "X"; // Enemy's position
        } else {
            cout << "-"; // Empty zone
        }

        if ((i + 1) % 3 == 0) {
            std::cout << std::endl;
        }
    }
}

// Function to get the player input
int getPlayerInput() {
    int input;
    cout << "Enter your move (0-3): ";
    cin >> input;
    return input;
}

// Game loop
void playGame() {
    bool gameOver = false;

    while (!gameOver) {
        displayGameWorld();
        cout << rooms[currentRoomIndex].description;

        int input = getPlayerInput();

        switch (input) {
            case 0:
            case 1:
            case 2:
            case 3:
                movePlayer(input);
                break;
            case 4:
                pickUpItem(1); // Assuming item ID1 is the sword
                break;
            case 5:
                useItem(1); // Assuming item ID 1 is the sword
                break;
            case 6:
            gameOver = true;
            cout << "Game over, You quit the game.";
            break;
        default:
            cout << "Invalid input";
        }

        // Check game over conditions, win conditions, or other game specific logic
        // .....
    }
}

// Main function
int main() {
    initializeGameWorld();
    playGame();

    return 0;
}