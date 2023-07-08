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
};

struct Item {
    int id;
    string name;
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

    // Add rooms 3 4 and 5 have room 3 go to room 2 4 and 5
}

// Initialize items
void initializeItems() {
    Item item1;
    item1.id = 1;
    item1.name = "Sword";
    item1.description = "A sharp sword.";
    items.push_back(item1);

    // Add wood and metal armor along with a club and sheild
}

// Initialize enemies
void initializeEnemies() {
    Enemy enemy1;
    enemy1.name = "Skeleton";
    enemy1.attack = 10;
    enemy1.defense = 5;
    enemy1.health = 20;
    enemies.push_back(enemy1);

    // add an enemy for rooms 4 and 5 say a zombie and vampire
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
        }
    } else {
        cout << "Cannot go in that direction";
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