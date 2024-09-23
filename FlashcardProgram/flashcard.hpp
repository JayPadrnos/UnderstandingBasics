#ifndef FLASHCARD_HPP
#define FLASHCARD_HPP

#include <string>

class FlashCard {
    public:
    std::string question;
    std::string answer;
    std::string hint;
    std::string questionImage; // Optional Image path for question
    std::string answerImage; // Optional Image path for answer
    int difficulty;         // 1 = easy, 2 = medium, 3 = hard

    FlashCard(std::string q, std::string a, std::string h, std::string qImg = "", std::string aImg = "", int diff = 1);
};

#endif