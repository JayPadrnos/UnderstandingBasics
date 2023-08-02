#include <iostream>
#include <string>

struct Character {
    std::string name;
    int health;
    int strength;
    int defense;
    int agility;
};

void attack(Character& attacker, Character& defender) {
    int damage = attacker.strength - defender.defense;
    if (damage > 0) {
        defender.health -= damage;
    }
}

int main() {
    Character character1;
    character1.name = "John";
    character1.health = 100;
    character1.strength = 80;
    character1.defense = 70;
    character1.agility = 60;

    Character character2;
    character2.name = "Jane";
    character2.health = 90;
    character2.strength = 70;
    character2.defense = 25;
    character2.agility = 85;

    Character* currentTurn = &character1;
    Character* opponent = &character2;

    bool isFightOver = false;

    while (!isFightOver) {
        // Display current turn information
        std::cout << "It's " << currentTurn->name << "'s turn." << std::endl;
        std::cout << "Health: " << currentTurn->health << std::endl;
        std::cout << "Strength: " << currentTurn->strength << std::endl;
        std::cout << "Defense: " << currentTurn->defense << std::endl;
        std::cout << "Agility: " << currentTurn->agility << std::endl;
        std::cout << std::endl;

        // Perform attack
        attack(*currentTurn, *opponent);

        // Check if the opponent is defeated
        if (opponent->health <= 0) {
            std::cout << opponent->name << " has been defeated!" << std::endl;
            isFightOver = true;
            break;
        }

        // Swap the turn between characters
        std::swap(currentTurn, opponent);

        // Prompt for continuing the fight
        std::cout << "Press Enter to continue the fight..." << std::endl;
        std::cin.ignore();
        std::cout << std::endl;
    }

    return 0;
}