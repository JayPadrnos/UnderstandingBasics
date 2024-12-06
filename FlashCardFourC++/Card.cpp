#include "Card.hpp"
#include <iostream>

// Constructor
Card::Card(const std::string& q, const std::string& ans, const std::string& glassType, const std::string& garnishType, const std::string& prepMethod, const std::string& img)
    : question(q), answer(ans), glass(glassType), garnish(garnishType), preparation(prepMethod), image(img) {}

// Method to display card details (use for debugging or during session)
inline void Card::displayCard() const {
    std::cout << "Question: " << question << std::endl;
    std::cout << "Answer: " << answer << std::endl;
    std::cout << "Glass: " << glass << std::endl;
    std::cout << "Garnish: " << garnish << std::endl;
    std::cout << "Preparation: " << preparation << std::endl;
    if (!image.empty()) {
        std::cout << "Image: " << image << std::endl;
    } else {
        std::cout << "No image available." << std::endl;
    }
}
//added?