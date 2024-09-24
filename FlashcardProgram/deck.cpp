#include "Deck.hpp"
#include <algorithm>
#include <random>
#include <fstream>
#include <stdexcept>
#include <string>

void Deck::addCard(const FlashCard& card) {
    cards.push_back(card);
}

void Deck::shuffleDeck() {
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(std::random_device()()));
}

void Deck::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string question, answer, hint, qImg, aImg;
    int difficulty;

    while (std::getline(file, question)) {
        std::getline(file, answer);
        std::getline(file, hint);
        std::getline(file, qImg);
        std::getline(file, aImg);
        file >> difficulty;
        file.ignore(); // Ignore the newline character after difficulty
        addCard(FlashCard(question, answer, hint, qImg, aImg, difficulty));
    }
}

void Deck::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& card : cards) {
        file << card.question << "\n"
            << card.answer << "\n"
            << card.hint << "\n"
            << card.questionImage << "\n"
            << card.answerImage << "\n"
            << card.difficulty << "\n";
    }
}

std::vector<FlashCard> Deck::filterByDifficulty(int level) {
    std::vector<FlashCard> filtered;
    for (const auto& card : cards) {
        if (card.difficulty == level) {
            filtered.push_back(card);
        }
    }
    return filtered;
}