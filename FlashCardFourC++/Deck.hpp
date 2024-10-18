#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include "Card.hpp"

class Deck {
public:
    std::string deckName;
    std::vector<Card> cards;

    Deck(const std::string& name, const std::vector<Card>& cardList);
};

Deck loadDrinksOfMixologyDeck();
Deck loadTypesOfLiquorDeck();

#endif // DECK_HPP
