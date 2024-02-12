#include "dictionary.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>

void Dictionary::addWord(const std::string& word, const std::string& pronunciation, const std::map<std::string, std::vector<std::string>>& typesAndDefinitions) {
    Word newWord;
    newWord.word = word;
    newWord.pronunciation = pronunciation;
    for (const auto& pair : typesAndDefinitions) {
        newWord.typesAndDefinitions.insert(pair);
    }
    words.push_back(newWord);
}

std::vector<Word> Dictionary::getRandomWords(int count) const {
    std::vector<Word> result;
    srand(time(nullptr));

    // Shuffle the words vector
    std::vector<Word> shuffledWords = words;
    std::random_shuffle(shuffledWords.begin(), shuffledWords.end());

    //Select the first 'count' words from the shuffled list
    for (int i = 0; i < count && i < shuffledWords.size(); ++i) {
        result.push_back(shuffledWords[i]);
    }
    return result;
}