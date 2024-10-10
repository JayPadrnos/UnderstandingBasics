#include  "UserSession.hpp"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

void UserSession::setDeck (Deck& deck) {
    this->deck = deck;
}

void UserSession::shuffleDeck() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::random_shuffle(deck.cards.begin(), deck.cards.end());
}

void UserSession::viewAllCards() {
    for (int i = 0; i < deck.cards.size(); ++i) {
        std::cout << i + 1 << ". " << deck.cards[i].question << std::endl;
    }
}

void UserSession::pickCard() {
    std::cout << "Enter the card number you'd like to see: ";
    int cardIndex;
    std::cin >> cardIndex;

    if (cardIndex >= 1 && cardIndex <= deck.cards.size()) {
        std::cout << "Question: " << deck.cards[cardIndex - 1].question << "\n";
        std::cout << "Answer: " << deck.cards[cardIndex - 1].answer << "\n";
    } else {
        std::cout << "Invalid card number.\n";
    }
}

void UserSession::run() {
    for (const auto& card : deck.cards) {
        std::cout << "Question: " << card.question << "\n";
        std::cout << "Press Enter to see the answer...\n";
        std::cin.get();
        std::cout << "Answer: " << card.answer << "\n\n";
    }
}