#ifndef USERSESSION_HPP
#define USERSESSION_HPP

#include "Deck.hpp"

class UserSession {
    public:
        void startSession(const Deck& deck);

    private:
        void displayCard(const Card& card);
        void shuffleDeck(std::vector<Card>& card);
        void displayAllCards(const Deck& deck);
        void manualCardSelection(const Deck& deck);
        void resetSession();
};


#endif // USERSESSION_HPP