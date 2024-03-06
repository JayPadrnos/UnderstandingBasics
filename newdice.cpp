#include <iostream>
#include <random>
#include <map>
#include <string>

class DiceRoller {
    public:
        DiceRoller() : sides(6) {}

        void setDiceSides(int sides) {
            this->sides = sides;
        }

        int roll() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, sides);
            return dis(gen);
        }

    private:
        int sides;
};

class Game {
    public:
        Game() {
            for (int i = 0; i < numDiceTypes; ++i) {
                diceTypes[i].first = std::to_string(4 * (i + 1));
                diceTypes[i].second = 4 * (i + 1);
            }
        }

        void handleInput() {
            char input;
            std::cout << "Choose dice type (4, 6, 8, 10, 20, 100): ";
            std::cin >> input;

            for (int i = 0; i < numDiceTypes; ++i) {
                if (diceTypes[i].first[0] == input) {
                    roller.setDiceSides(diceTypes[i].second);
                    return;
                }
            }

            std::cout << "Invalid input. Please choose from available dice types. " << std::endl;
        }

        void rollDice() {
            int result = roller.roll();
            std::cout << "You rolled a " << result << std::endl;
        }
    private:
        static const int numDiceTypes = 6;
        std::pair<std::string, int> diceTypes[numDiceTypes];
        DiceRoller roller;
};

int main() {
    Game game;

    while (true) {
        game.handleInput();
        game.rollDice();

        char choice;
        std::cout << "Roll again? (y/n): ";
        std::cin >> choice;

        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }

    return 0;
}