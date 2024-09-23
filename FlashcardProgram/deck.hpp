#ifndef DECK_HPP
#define DECK_HPP

#include "FlashCard.hpp"
#include <vector>

class Deck {
    public:
    std::vector<FlashCard> cards;

    void addCard(const FlashCard& card);
    void shuffleDeck();
    FlashCard getCard(int index);
    Deck filterByDifficulty(int difficultyLevel);
    int size() const;
};

#endif