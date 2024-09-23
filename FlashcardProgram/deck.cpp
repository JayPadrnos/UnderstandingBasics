#include "Deck.hpp"
#include <algorithm>
#include <random>
#include <stdexcept>

void Deck::addCard(const FlashCard& card) {
    cards.push_back(card);
}

void Deck::shuffleDeck() {
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(std::random_device()()));
}

FlashCard Deck:: getCard(int index) {
    if (index >= 0 && index < cards.size()) {
        return cards[index];
    } else {
        throw std::out_of_range("Invalid card index");
    }
}

Deck Deck::filterByDifficulty(int difficultyLevel) {
    Deck filteredDeck;
    for (const auto& card : cards) {
        if (card.difficulty == difficultyLevel) {
            filteredDeck.addCard(card);
        }
    }
    return filteredDeck;
}

int Deck::size() const {
    return cards.size();
}