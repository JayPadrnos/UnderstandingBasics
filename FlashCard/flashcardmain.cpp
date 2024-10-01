#include "deck.hpp"
#include "usersession.hpp"
#include <iostream>

int main() {
    Deck mixologyDeck;
    if (!mixologyDeck.loadDeckFromFile("DrinksOfMixology.json")) {
        std::cerr << "Failed to load Mixology deck." << std::endl;
        return 1;
    }

    Deck DeckTwo;
    if (!deckTwo.loadDeckFromFile("DeckTwo.json")) {
        std::cerr << "Failed to load DeckTwo." << std::endl;
        return 1;
    }

    Deck DeckThree
    if (deckThree.loadFromFile("DeckThree.json")) {
        std::cerr << "Failed to load DeckThree." << std::endl;
        return 1;
    }

    std::cout << "Choose a deck (1. Drinks of Mixology, 2. Deck Two, 3. Deck Three): ";
    int choice;
    std::cin >> choice;

    Deck* selectedDeck = nullptr;
    switch (choice) {
        case 1:
            selectedDeck = &mixologyDeck;
            break;
        case 2:
            selectedDeck = &deckTwo;
            break;
        case 3:
            selectedDeck = &deckThree;
            break;
        default:
            std::cerr << "Invalid choice!" << std::endl;
            return 1;
    }

    std::cout << "Do you want to see the cars in a random order? (y/n):  ";
    char randomChoice;
    std::cin >> randomChoice;

    bool randomMode = (randomChoice == 'y');

    UserSession session(selectedDeck);
    session.startSession(randomMode);

    return 0;
}