#include "dictionary.hpp"
#include <cstdlib>
#include <ctime>

void Dictionary::addWord(const std::string& word, const std::string& type, const std::vector<std::string>& pronunciation, const std::vector<std::string>& definitions) {
    Word newWord;
    newWord.word = word;
    newWord.type = type;
    newWord.pronunciation = pronunciation;
    newWord.definitions = definitions;
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