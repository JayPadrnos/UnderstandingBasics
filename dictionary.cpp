#include "dictionary.hpp"
#include <cstdlib>
#include <ctime>

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
    for (int i = 0; i < count; ++i) {
        int index = rand() % words.size();
        result.push_back(words[index]);
    }
    return result;
}