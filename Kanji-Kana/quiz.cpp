#include <iostream>
#include "quiz.h"
#include "numbergen.h"

void runQuiz(const Library& lib) {
    const auto& words = lib.getWords();
    if (words.empty()) {
        std::cout << "Library is empty.\n";
        return;
    }

    // Ask user which random method to use
    std::cout << "Select quiz method: 1. Random  2. Word of the Day\n";
    int choice; std::cin >> choice;
    RandomMethod method = (choice == 2) ? RandomMethod::WORD_OF_THE_DAY : RandomMethod::RANDOM;

    // Example: quiz 3 words
    std::vector<int> indices = getUniqueRandomNumbers(words.size(), 3);

    for (int idx : indices) {
        if (method == RandomMethod::WORD_OF_THE_DAY)
            idx = getRandomNumber(words.size(), RandomMethod::WORD_OF_THE_DAY);

        const auto& w = words[idx];
        std::string answer;
        std::cout << "\nTranslate this word into English: " 
                  << w.kana << " (" << w.romaji << ")\n";
        std::cout << "Your answer: ";
        std::cin >> answer;

        if (answer == w.english) {
            std::cout << "Correct!\n";
        } else {
            std::cout << "Wrong. Correct answer: " << w.english << "\n";
        }
    }
}


// add dif quizes here

// quizes for sentences, one version with fill in the blank and one as a romanji and one as what is this sentence in english
// fill in the blank and romanji should be down first
