#pragma once
#include <string>
#include <vector>

class Card {
    private:
        std::string question;
        std::string glass;
        std::vector<std::pair<std::string, std::string>> ingredients; //Name and Amount
        std::string garnish;
        std::vector<std::pair<std::string, std::string>> variations; // Type and description
        std::string preparation;

    public:
        Card(const std::string& q, const std::string& g,
             const std::vector<std::pair<std::string, std::string>>& ing,
             const std::string gar,
             const std::vector<std::pair<std::string, std::string>>& var,
             const std::string& prep)
            : question(q), glass(g), ingredients(ing), garnish(gar), variations(var), preparation(prep) {}

        // Getters
        std::string getQuestion() const {return question; }
        std::string getGlass() const { return glass; }

        std::vector<std::pair<std::string, std::string>> getIngredients() const { return ingredients; }
        std::string getGarnish() const { return garnish; }

        std::vector<std::pair<std::string, std::string>> getVariations() const { return variations; }
        std::string getPreparation() const { return preparation; }
};