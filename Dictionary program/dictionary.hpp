#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <vector>
#include <map>

struct Word
{
    std::string word;
    std::string pronunciation;
    std::map<std::string, std::vector<std::string>> typesAndDefinitions;
};

class Dictionary
{
    private:
        std::vector<Word> words;

    public:
        void addWord(const std::string&word, const std::string& pronunciation, const std::map<std::string , std::vector<std::string>>& typesAndDefinitions);
        std::vector<Word> getRandomWords(int count) const;
};

#endif // DICTIONARY_HPP