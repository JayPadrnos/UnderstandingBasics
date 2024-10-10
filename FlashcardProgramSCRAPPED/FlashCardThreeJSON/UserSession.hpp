#ifndef USERSESSION_HPP
#define USERSESSION_HPP

#include "Deck.hpp"
#include <vector>
#include <string>

class UserSession {
    private:
        Deck deck;
        int correctAnswers;
        int currentCardIndex;
        std::vector<bool> answeredCorrectly;

    public:
        UserSession(const Deck& d);
        void start();
        void trackAnswer (bool correct);
        void reviewSession() const;
        int getFinalScore() const;
};

#endif