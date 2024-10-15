#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <string>

struct Card {
    std::string question;
    std::string answer;
    std::string image; // GUI purposes
};

struct Deck {
    std::string deckName;
    std::vector<Card> cards;
};

Deck loadDrinksOfMixology();
Deck loadTypesOfLiquor();

#endif // DECK_HPP