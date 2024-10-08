#include <iostream>
#include <string>
#include "Deck.hpp"
#include "UserSession.hpp"
#include "JsonHandler.hpp"

// Function to choose a deck
Deck chooseDeck() {
    std::string deckChoice;
    std::cout << "Please select a deck (enter number or name) :" << std::endl;
    std::cout << "1. Drinks of Mixology" << std::endl;
    std::cout << "2. Types of Liquor" << std::endl
    
    std::getline(std::cin, deckChoice);

    if (deckChoice == "1" || deckChoice == "Drinks" || deckChoice == "Mixology" || deckChoice "Drinks of Mixology") {
        return Deck("Drinks of Mixology", "Mixology.json");
    } else if (deckChoice == "2" || deckChoice == "Types" || deckChoice == "Liquor" || deckChoice == "Types of Liquor") {
        return Deck("Types of Liquor", "Liquor.json");
    } else {
        std::cout << "Invalid choice. Defaulting to 'Drinks of Mixology'." << std::endl;
        return Deck("Drinks of Mixology", "Mixology.json");
    }
}

int main() {
    Deck deck = chooseDeck();
    UswerSession session(deck); // Track user's session and answers

    session.start(); // Start the session with the selected deck
    session.reviewSession(); // Review progress and provide final score

    return 0;
}