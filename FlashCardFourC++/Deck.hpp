#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <string>

struct Card {
    std::string question;
    std::string answer;
};

class Deck {
    public:
        std::vector<Card> cards;
        Deck() = default;
};

Deck loadDrinksOfMixology();
Deck loadTypesOfLiquor();

#endif // DECK_HPP