#include "drinks_of_mixology.hpp"
#include "Card.hpp"

std::vector<Card> loadDrinksOfMixologyDeck() {
    std::vector<Card> drinksDeck = {
        Card("What is a Martini?", "A cocktail made with gin and vermouth, garnished with an olive", "Cocktail Glass", "Olive", "Shaken or Stirred"),
        // Add more cards as needed
    };
    return drinksDeck;
}
