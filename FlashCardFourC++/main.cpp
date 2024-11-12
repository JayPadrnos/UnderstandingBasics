#include <iostream>
#include "UserSession.hpp"
#include "Deck.hpp"

void displayMenu() {
    std::cout << "Welcome to the Flashcard Program!" << std::endl;
    std::cout << "Choose a deck to begin:" << std::endl;
    std::cout << "1. Drinks of Mixology" << std::endl;
    std::cout << "2. Types of Liquor" << std::endl;
    std::cout << "3. Exit" << std::endl;
}

int main() {
    bool running = true;

    while (running) {
        displayMenu();

        int deckChoice;
        std::cin >> deckChoice;

        Deck selectedDeck("", {});
        std::string deckName;

        switch (deckChoice) {
            case 1:
                selectedDeck = loadDrinksOfMixologyDeck();
                deckName = "Drinks of Mixology";
                break;
            case 2:
                selectedDeck = loadTypesOfLiquorDeck();
                deckName = "Types of Liquor";
                break;
            case 3:
                std::cout << "Exiting program..." << std::endl;
                running = false;
                continue;
            default:
                std::cout << "Invalid choice. Please select a valid deck." << std::endl;
                continue;
        }

        if (!selectedDeck.cards.empty()) {
            UserSession session;
            std::cout << "\nDeck \"" << deckName << "\" loaded!" << std::endl;
            session.startSession(selectedDeck);
        } else {
            std::cout << "Failed to load the deck." << std::endl;
        }
    }

    return 0;
}
