#include <iostream>
#include <string>

struct Character {
    std::string name;
    int health;
    int strength;
    int defense;
    int agility;
    int intelligence;
    int charisma;
    int luck;
};

int main() {
    Character character;
    
    // Set character's stats
    character.name = "John";
    character.health = 100;
    character.strength = 80;
    character.defense = 70;
    character.agility = 60;
    character.intelligence = 75;
    character.charisma = 80;
    character.luck = 50;

    // Access and display character's stats
    std::cout << "Name: " << character.name << std::endl;
    std::cout << "Health: " << character.health << std::endl;
    std::cout << "Strength: " << character.strength << std::endl;
    std::cout << "Defense: " << character.defense << std::endl;
    std::cout << "Agility: " << character.agility << std::endl;
    std::cout << "Intelligence: " << character.intelligence << std::endl;
    std::cout << "Charisma: " << character.charisma << std::endl;
    std::cout << "Luck: " << character.luck << std::endl;
    
    return 0;
}