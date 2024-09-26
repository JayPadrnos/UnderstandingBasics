#ifndef USERSESSION_HPP
#define USERSESSION_HPP

#include "Deck.hpp"
#include <chrono>
#include <vector>

class UserSession {
    private:
    Deck& deck;
    int currentCard;
    int correctCount;
    int incorrectCount;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::vector<FlashCard> incorrectCards;
    bool isSequential;

    public:
    UserSession(Deck& d, bool seq = true);
    void shuffleOrNot();
    void startTimer();
    double endTimer();
    FlashCard getCurrentCard();
    void nextCard(bool correct);
    bool hasNextCard() const;
    void displayProgress() const;
    void reviewIncorrectCards() const;
    void showHint(const FlashCard& card);
};

#endif