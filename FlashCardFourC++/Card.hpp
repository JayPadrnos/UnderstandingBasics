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
    std::string image; // Image field for GUI purposes

    // Constructor
    Card(const std::string& q, const std::string& ans, const std::string& glassType, const std::string& garnishType, const std::string& prepMethod, const std::string& img = "");

    // Method to display card details (for debugging or use in session)
    void displayCard() const;
};

#endif
