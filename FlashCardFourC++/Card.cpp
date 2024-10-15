#include "Card.hpp"
#include <iostream>

Card::Card(const std::string& q, const std::string& ans, const std::string& glassType, const std::string& garnishType, const std::string& prepMethod)
 : question(q), answer(ans), glass(glassType), garnish(garnishType), preparation(prepMethod) {}

 // Method to display card details (use for debugging)
 void Card::displayCard() const {
    std::cout << "Question: " << question << std::endl;
    std::cout << "Answer: " << answer << std::endl;
    std::cout << "Glass: " << glass << std::endl;
    std::cout << "Garnish: " << garnish << std::endl;
    std::cout << "Preparation: " << preparation << std::endl;
 }