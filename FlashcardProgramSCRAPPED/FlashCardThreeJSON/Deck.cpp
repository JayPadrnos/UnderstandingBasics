#include "Deck.hpp"
#include "JsonHandler.hpp"

Deck::Deck(const std::string& name, const std::string& file) : deckName(name), fileName(file) {
    cards = JsonHandler::loadDeckFromFile(fileName);
}

const std::vector<nlohmann::json>& Deck::getCards() const {
    return cards;
}

std::string Deck::getName() const {
    return deckName;
}