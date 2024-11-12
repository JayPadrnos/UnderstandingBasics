#ifndef DECK_HPP
#define DECK_HPP

#include "FlashCard.hpp"
#include <vector>

class Deck {
    public:
    std::vector<FlashCard> cards;

    void addCard(const FlashCard& card);
    void shuffleDeck();
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    std::vector<FlashCard> filterByDifficulty(int);
};

#endif