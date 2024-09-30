#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "card.hpp"
#include "nlohmann/json.hpp"

class Deck {
    private:
        std::string name;
        std::vector<Card> card;

    public:
        Deck() = default;

        // Load deck from a JSON file
        bool loadDeckFromFile(const std::string& filename) {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Error opening file: " << filename << std::endl;
                return false;
            }

            nlohmann::json deckJson;
            file >> deckJson;
            name = deckJson["deck_name"];
            for (const auto& cardJson : deckJson["cards"]) {
                std::string question = cardJson["question"];
                std::string glass = cardJson["glass"];
                std::vector<std::pair<std::string, std::string>> ingredients;
                for (const auto& ing : cardJson["ingredients"]) {
                    ingredients.emplace_back(ing["name"], ing["amount"]);
                }
                std::string garnish = cardJson["garnish"];
                std::vector<std::pair<std::string, std::string>> variations;
                for (const auto& var : cardJson["variations"]) {
                    variations.emplace_back(var["type"], var["description"]);
                }
                std::string preparation = cardJson["preparation"];

                Card card(question, glass, ingredients, garnish, variations, preparation);
                cards.push_back(card);
            }

            return true;
        }

        const std::string& getName() const { return name; }
        const std::vector<Card& getCards() const { return cards; }
        Card getCard(int index) const { return cards[index]; }
        size_t size() const {return cards.card.size(); }
};