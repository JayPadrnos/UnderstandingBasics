#ifndef USERSESSION_HPP
#define USERSESSION_HPP

#include "Deck.hpp"

class UserSession {
    private:
        Deck deck;
    public:
        void setDeck (Deck& deck);
        void shuffleDeck();
        void viewAllCards();
        void pickCard();
        void run(); // Simulates going through the deck
};

#endif // USERSESSION_HPP