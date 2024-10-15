#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card {
    public:
        std::string question;
        std::string answer;
        std::string glass;
        std::string garnish;
        std::string preparation;

        // Constructor
        Card(const std::string& q, const std::string& ans, const std::string& glassType, const std::string& garnishType, const std::string& prepMethod);

        // Function to display card details 
        void displayCard() const;
};

#endif