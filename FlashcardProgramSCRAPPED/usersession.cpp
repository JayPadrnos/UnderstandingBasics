#include "UserSession.hpp"
#include <iostream>

UserSession::UserSession(Deck& d, bool seq) : deck(d), currentCard(0), correctCount(0), incorrectCount(0), isSequential(seq) {
    shuffleOrNot();
}

void UserSession::shuffleOrNot() {
    if (!isSequential) {
        deck.shuffleDeck();
    }
}

void UserSession::startTimer() {
    startTime = std::chrono::high_resolution_clock::now();
}

double UserSession::endTimer() {
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;
    return elapsed.count();
}

FlashCard UserSession::getCurrentCard() {
    return deck.getCard(currentCard);
}

void UserSession::nextCard(bool correct) {
    if (correct) {
        correctCount++;
    } else {
        incorrectCount++;
        incorrectCards.push_back(deck.getCard(currentCard)); // Store incorrect cards
    }
    currentCard++;
}

bool UserSession::hasNextCard() const {
    return currentCard < deck.size();
}

void UserSession::displayProgress() const {
    std::cout << "Progress: " << correctCount << " correct, " << incorrectCount << " incorrect. " << std::endl;
}

void UserSession::reviewIncorrectCards() const {
    if (incorrectCards.empty()) {
        std::cout << "No cards to review! You got everything correct. \n";
        return;
    }

    std::cout << "Reviewing incorrect cards::\n";
    for (const auto& card : incorrectCards) {
        std::cout << "Question: " << card.question << "\n";
        std::cout << "Correct Answer: " << card.answer << "\n\n";
    }
}

void UserSession::showHint(const FlashCard& card) {
    std::cout << "Hint: " << card.hint << std::endl;
}