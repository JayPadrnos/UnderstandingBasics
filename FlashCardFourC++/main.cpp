#include "Deck.hpp"
#include "UserSession.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

void displayMenu() {
    std::cout << "Flashcard Program\n";
    std::cout << "1. Drinks of Mixology\n";
    std::cout << "2. Types of Liquor\n";
    std::cout << "Enter the number or name of the deck you want to choose: ";
}

void displayDeckOptions() {
    std::cout << "\nDeck Options:\n";
    std::cout << "1. Shuffle deck\n";
    std::cout << "2. See all cards\n";
    std::cout << "3. Pick a card manually\n";
    std::cout << "4. Reset deck\n";
    std::cout << "\nEnter your choice: ";
}

int main() {
    std::vector<Deck> availableDecks = {loadDrinksOfMixology(), loadTypesOfLiquor()};
    UserSession session;

    std::string userInput;
    while (true) {
        displayMenu();
        std::getline(std::cin, userInput);

        // Deck selection
        Deck* chosenDeck = nullptr;
        if (userInput == "1" || userInput == "Drinks" || userInput == "Mixology" || userInput == "Drinks of Mixology") {
            chosenDeck = & availableDecks[0];
        } else if (userInput == "2" || userInput == "Liquor" || userInput == "Types of Liquor") {
            chosenDeck = &availableDecks[1];
        }

        if (chosenDeck){
            session.setDeck(*chosenDeck);

            // Deck options
            while (true) {
                displayDeckOptions();
                std::getline(std::cin, userInput);

                if (userInput == "1") { // Shuffle Deck
                    session.shuffleDeck();
                    session.run();
                } else if (userInput == "2") { // See all cards
                    session.viewAllCards();
                } else if (userInput == "3") { // Pick a card manually
                    session.pickCard();
                } else if (userInput == "4") { // Reset deck
                    break;
                } else {
                    std::cout << "Invalid choice. Try again.\n";
                }
            }
        } else {
            std::cout << "Invalid deck selection. Please try again.\n";
        }
    }
    return 0;
}