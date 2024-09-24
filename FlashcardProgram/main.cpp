#include "FlashCard.hpp"
#include "Deck.hpp"
#include "UserSession.hpp"
#include <iostream>

void createUserDeck(Deck& deck) {
    int cardCount;
    std::cout << "How many cards would you like to add?: ";
    std::cin >> cardCount;
    std::cin.ignore(); // clear newline from buffer

    for (int i = 0; i < cardCount; ++i) {
        std::string question, answer, hint;
        int difficulty;
        std::cout << "Enter question for card " << i + 1 << ": ";
        std::getline(std::cin, question);
        std::cout << "Enter answer for card " << i + 1 << ": ";
        std::getline(std::cin, answer);
        std::cout << "Enter hint for card " << i + 1 << ": ";
        std::getline(std::cin, hint);
        std::cout << "Enter difficulty level (1 = easy, 2 = medium, 3 = hard): ";
        std::cin >> difficulty;
        std::cin.ignore();

        deck.addCard(FlashCard(question, answer, hint, "", "", difficulty));
    }
}

int main() {
    Deck deck;
    std::string filename;

    std::cout << "Enter deck filename to load ( or type 'new' to create a new deck): ";
    std::getline(std::cin, filename);

    if (filename != "new") {
        deck.loadFromFile(filename);
    } else {
        createUserDeck(deck);
        std::cout << "Enter filename to save this deck: ";
        std::getline(std::cin, filename);
        deck.saveToFile(filename);
    }

    
}