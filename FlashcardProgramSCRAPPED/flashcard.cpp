#include "FlashCard.hpp"

FlashCard::FlashCard(std::string q, std::string a, std::string h, std::string qImg, std::string aImg, int diff)
    : question(q), answer(a), hint(h), questionImage(qImg), answerImage(aImg), difficulty(diff) {}