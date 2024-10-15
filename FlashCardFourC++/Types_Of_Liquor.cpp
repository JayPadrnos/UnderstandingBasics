#include "types_of_liquor.hpp"
#include "Card.hpp"

std::vector<Card> loadTypesOfLiquorDeck() {
    std::vector<Card> liquorDeck = {
        Card("What is Vodka?", "A clear distilled alcoholic beverage made from fermented grains or potatoes", "", "", ""),
        Card("What is Bourbon?", "A type of American whiskey, primarily made from corn", "", "", ""),
        // Add more cards as needed
    };
    return liquorDeck;
}
