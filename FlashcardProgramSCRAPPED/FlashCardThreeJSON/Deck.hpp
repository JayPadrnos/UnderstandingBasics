#ifndef DECK_HPP
#define DECK_HPP

#include <string> 
#include <vector>
#include <nlohmann/json.hpp>

class Deck {
    private:
        std::string deckName;
        std::string fileName;
        std::vector<nlohmann::json> cards;

    public:
        Deck(const std::string& name, const std::string& file);
        const std::vector<nlohmann::json>& getCards() const;
        std::string getName() const;
};

#endif