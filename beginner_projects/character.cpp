#include <iostream>
#include <string>
using namespace std;

struct Character {
    string name;
    int health;
    int strength;
    int defense;
    int agility;
    int intelligence;
    int charisma;
    int luck;
};

    void attack(Character& attacker, Character& defender) {
        int damage = attacker.strength - defender.defense;
        if (damage > 0) {
            defender.health -= damage;
        }
    }

int main() {

    // Set character stats
    Character character1;
    character1.name = "Chud";
    character1.health = 100;
    character1.strength = 35;
    character1.defense = 50;
    character1.agility = 30;
    character1.intelligence = 20;
    character1.charisma = 10;
    character1.luck = 40;

    Character character2;
    character2.name = "Cannonfodder";
    character2.health = 50;
    character2.strength = 25;
    character2.defense = 25;
    character2.agility = 20;
    character2.intelligence = 10;
    character2.charisma = 15;
    character2.luck = 10;

    Character* currentTurn = &character1;
    Character* opponent = &character2;

    bool isFightOver = false;

    while (isFightOver) {
        // Displays current turn info
        cout << "It's " << currentTurn->name << "'s turn." << endl;
        cout << "Health: " << currentTurn->health << endl;
        cout << "Strength " << currentTurn->strength << endl;
        cout << "Defense " << currentTurn->defense << endl;
        cout << "Agility " << currentTurn->agility << endl;
        cout << "Intelligence " << currentTurn->intelligence << endl;
        cout << "Charisma " << currentTurn->charisma << endl;
        cout << "Luck " << currentTurn->luck << endl;
        cout << endl;
        
        // Performs attack
        attack(*currentTurn, *opponent);

        // Check if the opponent is defeated
        if (opponent->health <= 0) {
            cout << opponent->name << " has been defeated!" <<endl;
            isFightOver = true;
            break;
        }

        // Swaps turns between characters
        swap(currentTurn, opponent);

        // Prompt for continuing the fight
        cout << "Press Enter to continue the fight.... " << endl;
        cin.ignore();
        cout << endl;

    }

    return 0;
}





