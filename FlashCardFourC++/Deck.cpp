#include "Deck.hpp"

// Load the Drinks of Mixology deck
Deck loadDrinksOfMixology() {
    Deck deck;
    deck.cards.push_back({"What is a Martini?", "Cocktail Glass\n2ozGin / Or Vodka\n1/2oz Dry Vermouth\nGarnish: Olive\nDirty add splash of Olive Juice\nDry/Naked: No Vermouth\nOn the Rocks: Lowball with Ice"});
    // Add more cards here for Mixology
    return deck;
}

// Load the Types of Liquor deck
Deck loadTypesOfLiquor() {
    Deck deck;
    deck.cards.push_back({"What is Vodka?", "A neutral spirit distilled from fermented grains or potatoes."});
    deck.cards.push_back({"What is Bourbon?", "A type of American whiskey made primarily from corn."});
    deck.cards.push_back({"What is Tequila?", "A distilled beverage made from the blue agave plant."});
    // Add more for Liquor types 
    return deck;
}