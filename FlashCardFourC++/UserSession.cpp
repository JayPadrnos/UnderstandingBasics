#include "UserSession.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <string>

// Start session with the selected deck
void UserSession::startSession(const Deck& deck) {
    std::string mode;
    std::cout << "Choose a mode: shuffle, all, or manual: ";
    std::cin.ignore();
    std::getline(std::cin, mode);

    if (mode == "shuffle") {
        std::vector<Card> shuffledCards = deck.cards;
        shuffleDeck(shuffledCards);
        for (const auto& card : shuffledCards) {
            displayCard(card);
        }
    } else if (mode == "all") {
        displayAllCards(deck);
    } else if (mode == "manual") {
        manualCardSelection(deck);
    } else {
        std::cout << "Invalid mode.\n";
    }

    resetSession();
}

// Display a single card (question, answer, and image)
void UserSession::displayCard(const Card& card) {
    std::cout << "Question: " << card.question << "\n";
    std::cout << "Answer: " << card.answer << "\n";
    if (!card.image.empty()) {
        std::cout << "Image: " << card.image << "\n";
    } else {
        std::cout << "No image available.\n";
    }
    std::cout << "Glass: " << card.glass << "\n";
    std::cout << "Garnish: " << card.garnish << "\n";
    std::cout << "Preparation: " << card.preparation << "\n";
}

// Shuffle the deck randomly
void UserSession::shuffleDeck(std::vector<Card>& cards) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

// Display all cards in the deck
void UserSession::displayAllCards(const Deck& deck) {
    for (const auto& card : deck.cards) {
        displayCard(card);
    }
}

// Manually select a card from the deck
void UserSession::manualCardSelection(const Deck& deck) {
    std::string choice;
    std::cout << "Enter the card number (1- " << deck.cards.size() << "): ";
    std::getline(std::cin, choice);
    int cardIndex = std::stoi(choice) - 1;

    if (cardIndex >= 0 && cardIndex < deck.cards.size()) {
        displayCard(deck.cards[cardIndex]);
    } else {
        std::cout << "Invalid card number.\n";
    }
}

// Reset the session (this can be extended for more functionality)
void UserSession::resetSession() {
    std::cout << "Session reset.\n";
}
