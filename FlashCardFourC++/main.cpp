#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for random_shuffle
#include "UserSession.hpp"
#include "drinks_of_mixology.hpp"
#include "types_of_liquor.hpp"
#include "Card.hpp"

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

        std::vector<Card> selectedDeck;
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

        if (!selectedDeck.empty()) {
            UserSession session(selectedDeck);

            std::cout << "\nDeck \"" << deckName << "\" loaded!" << std::endl;
            std::cout << "Would you like to (1) shuffle deck, (2) browse cards, or (3) pick a card by number?" << std::endl;
            int action;
            std::cin >> action;

            switch (action) {
                case 1:
                    session.shuffleDeck();
                    session.quiz(); // Start quiz in shuffled order
                    break;
                case 2:
                    session.browseDeck(); // Browse all cards
                    break;
                case 3: {
                    std::cout << "Enter card number to view: ";
                    int cardNum;
                    std::cin >> cardNum;
                    session.pickCard(cardNum); // Manually pick a card
                    break;
                }
                default:
                    std::cout << "Invalid action. Please choose a valid option." << std::endl;
            }

            std::cout << "Your score: " << session.getFinalScore() << " out of " << session.getTotalCards() << "!" << std::endl;
        } else {
            std::cout << "Failed to load the deck." << std::endl;
        }
    }

    return 0;
}
//