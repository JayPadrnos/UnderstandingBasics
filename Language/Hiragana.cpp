#include "Hiragana.hpp"
#include <iostream>

// Constructor: Initializes the Hiragana alphabet
Hiragana::Hiragana() {
    // Load the alphabet data from a file or initialize it here
    // For simplicity, you can initialize it within the constructor
    hiraganaAlphabet = {
        {"あ", "a"}, {"い", "i"}, {"う", "u"}, {"え", "e"}, {"お", "o"},
        {"か", "ka"}, {"き", "ki"}, {"く", "ku"}, {"け", "ke"}, {"こ", "ko"},
        {"さ", "sa"}, {"し", "shi"}, {"す", "su"}, {"せ", "se"}, {"そ", "so"},
        {"た", "ta"}, {"ち", "chi"}, {"つ", "tsu"}, {"て", "te"}, {"と", "to"},
        {"な", "na"}, {"に", "ni"}, {"ぬ", "nu"}, {"ね", "ne"}, {"の", "no"},
        {"は", "ha"}, {"ひ", "hi"}, {"ふ", "fu"}, {"へ", "he"}, {"ほ", "ho"},
        {"ま", "ma"}, {"み", "mi"}, {"む", "mu"}, {"め", "me"}, {"も", "mo"},
        {"や", "ya"}, {"ゆ", "yu"}, {"よ", "yo"},
        {"ら", "ra"}, {"り", "ri"}, {"る", "ru"}, {"れ", "re"}, {"ろ", "ro"},
        {"わ", "wa"}, {"を", "wo"}, {"ん", "n"}
    };
}

// Display the Hiragana alphabet and their pronunciations
void Hiragana::displayAlphabet() const {
    for (const HiraganaCharacter& h : hiraganaAlphabet) {
        std::cout << h.character << " (" << h.pronunciation << ") ";
    }
    std::cout << "\n";
}