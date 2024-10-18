#ifndef USERSESSION_HPP
#define USERSESSION_HPP

#include "Deck.hpp"

class UserSession {
public:
    void startSession(const Deck& deck); // Start the session based on user input

private:
    void displayCard(const Card& card); // Display a single card
    void shuffleDeck(std::vector<Card>& card); // Shuffle the deck
    void displayAllCards(const Deck& deck); // Display all cards in the deck
    void manualCardSelection(const Deck& deck); // Allow user to manually select a card
    void resetSession(); // Reset the session
};

#endif // USERSESSION_HPP
