#include <iostream>
#include "library.h"
#include "numbergen.h"

Library::Library() {
    // Preload library with 10 words
    words.push_back({"あい", "ai", "love"});
    words.push_back({"あお", "ao", "blue"});
    words.push_back({"あし", "ashi", "foot"});
    words.push_back({"いえ", "ie", "house"});
    words.push_back({"いぬ", "inu", "dog"});
    words.push_back({"ねこ", "neko", "cat"});
    words.push_back({"みず", "mizu", "water"});
    words.push_back({"ひと", "hito", "person"});
    words.push_back({"くるま", "kuruma", "car"});
    words.push_back({"やま", "yama", "mountain"});
}

void Library::displayAllWords() const {
    std::cout << "\n--- Library ---\n";
    int index = 1;
    for (const auto& w : words) {
        std::cout << index++ << ". " 
                  << w.kana << " (" << w.romaji << ") - " 
                  << w.english << "\n";
    }
}

void Library::displayWordOfTheDay() {
    if (words.empty()) return;

    int idx = getRandomNumber(words.size(), RandomMethod::WORD_OF_THE_DAY);
    const auto& w = words[idx];

    std::cout << "\n=== Word of the Day ===\n";
    std::cout << w.kana << " (" << w.romaji << ") - " << w.english << "\n";
    std::cout << "=======================\n";
}

const std::vector<WordEntry>& Library::getWords() const {
    return words;
}


