#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <vector>

struct Word
{
    std::string word;
    std::string type;
    std::vector<std::string> pronunciation;
    std::vector<std::string> definitions;
};

class Dictionary 
{
    private:
        std::vector<Word> words;

    public:
        void addWord(const std::string& word, const std::string& type, const std::vector<std::string>& pronunciations, const std::vector<std::string>& definitions);
        std::vector<Word> getRandomWords(int count) const;
};

#endif // DICTIONARY_HPP