#ifndef DICEROLL_HPP
#define DICEROLL_HPP

#include <string>

class DiceGame {
    public:
        void play();
        int rollDice(int sides);
        bool playAgain();
};

#endif // DICEROLL_HPP