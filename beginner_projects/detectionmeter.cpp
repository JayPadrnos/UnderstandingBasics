#include <iostream>
using namespace std;

class Character {
    private:
        string name;
        int age;
        int current_health;
        int max_health;
        int strength;
        int dexterity;
        int defense;
    public:
        Character(const string& characterName, int characterAge, int characterCurrentHP, int characterMaxHP, int characterStrength, int characterDexterity, int characterDefense) {
            name = characterName;
            age = characterAge;
            current_health = characterCurrentHP;
            max_health = characterMaxHP;
            strength = characterStrength;
            dexterity = characterDexterity;
            defense = characterDefense;   
        }

        int getCurrentHealth() const {
            return current_health;
        }

        void attack(Character& attacker, Character& defender) {
            int damage = attacker.strength - defender.defense;
            if (damage > 0) {
                defender.current_health -= damage;
            }
            cout << name << "Swings their sword at the beast.\n\n";
            cout << defender.name << " has " << defender.current_health << "/" << defender.max_health << "HP after that hit. \n\n";
        }
};

int main() {
    Character player("Player", 20, 100, 100, 25, 10, 20);
    Character enemy("Enemy", 50, 75, 75, 25, 10, 10);

    bool isPlayerTurn = true;
    bool isBattleOver = false;

    while (!isBattleOver) {
        if (isPlayerTurn) {
            cout << "It is currently Player's turn, take an action: \n";
            cout << "1. Attack\n";
            cout << "2. Defend\n";
            cout << "3. Run away\n";
            int choice;
            cin >> choice;

        switch (choice) {
            case 1:
                player.attack(player, enemy);
                break;
            case 2:
                cout << "Player takes a defensive stance. \n";
                break;
            case 3:
                cout << "Player runs away from the fight. \n";
                isBattleOver = true;
                break;
            default:
                cout << "invalid choice. Turn skipped. \n";
            }
        } else {
            cout << "Enemy's turn. \n";
            enemy.attack(enemy, player);
        }

        if (player.getCurrentHealth() <= 0 || enemy.getCurrentHealth() <= 0) {
            isBattleOver = true;
            if (player.getCurrentHealth() <= 0) {
                cout << "Player has been defeated. Game Over! \n";

         } else {
                cout << "Enemy has been defeated. You Win! \n";
           }
        }

        isPlayerTurn = !isPlayerTurn;
        }

    return 0;


}