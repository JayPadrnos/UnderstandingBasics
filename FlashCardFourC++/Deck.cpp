#include "Deck.hpp"

// Constructor for Deck
Deck::Deck(const std::string& name, const std::vector<Card>& cardList)
    : deckName(name), cards(cardList) {}

// Loading Drinks of Mixology Deck
Deck loadDrinksOfMixologyDeck() {
    std::vector<Card> drinksDeck = {
        Card("What is a Martini?", "A cocktail made with gin and vermouth, garnished with an olive", "Cocktail Glass", "Olive", "Shaken or Stirred"),
        // Add more cards as needed
    };
    return Deck("Drinks of Mixology", drinksDeck);
}

// Loading Types of Liquor Deck
Deck loadTypesOfLiquorDeck() {
    std::vector<Card> liquorDeck = {
        Card("What is Vodka?", "A clear distilled alcoholic beverage made from fermented grains or potatoes", "", "", ""),
        Card("What is Bourbon?", "A type of American whiskey, primarily made from corn", "", "", ""),
        // Add more cards as needed
    };
    return Deck("Types of Liquor", liquorDeck);
}
