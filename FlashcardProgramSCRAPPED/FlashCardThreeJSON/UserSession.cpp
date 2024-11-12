#include "UserSession.hpp"
#include <iostream>

UserSession::UserSession(const Deck& d) : deck(d), correct(0), currentCardIndex(0) {
    answeredCorrectly.resize(deck.getCards().size(), false);
}

void UserSession::start() {
    const auto& cards = deck.getCards();
    std::string userAnswer;

    for (currentCardIndex = 0; currentCardIndex < cards.size(); ++currentCardIndex) {
        std::cout << "Card" << (currentCardIndex + 1) << "/" << cards.size() << ": " << cards[currentCardIndex]["question"] << std::endl;
        std::getline(std::cin, userAnswer);

        // For now, simple string comparision, you can refine this later
        if (userAnswer == cards[currentCardIndex]["answer"]) {
            std::cout << "Correct!" << std::endl;
            trackAnswer(true);
        } else {
            std::cout << "Incorrect. Correct answer: " << cards[currentCardIndex]["answer"] << std::endl;
            trackAnswer(false);
        }
    }
}

void UserSession::trackAnswer(bool correct) {
    answeredCorrectly[currentCardIndex] = correct;
    if (correct) correctAnswers++;
}

void UserSession::reviewSession() const {
    std::cout << "Session Complete!" << std::endl;
    std::cout << "You got " << correctAnswers << " out of " << deck.getCard().size() << " correct." << std::endl;
}

int UserSession::getFinalScore() const {
    return correctAnswers;
}