#ifndef WORD_MANAGER_HPP
#define WORD_MANAGER_HPP

#include <string>
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <iostream>

class WordManager {
    private:
        struct WordDetails {
            std::string pronunciation;
            std::string definitions;
            std::string noun;
            std::string verb;
            std::string adjective;
            std::string wordType;
            bool userAdded; // Flag to indicate if added by user
        };

        std::unordered_map<std::string, WordDetails> wordDatabase;
        const std::string dataFileName = "Word_Library.txt";

        void loadWordData();
        void saveWordData() const;

        // Timer-based autosave
        void startAutosave();
        void autosave();

        // Session persistence
        std::string lastWordViewed;

    public:
        WordManager();
        ~WordManager();

        void addWord(const std::string& word, const WordDetails& details);
        void defineWord(const std::string& word, const std::string& definitions);
        void addAndDefine(const std::string& word, const WordDetails& details, const std::string& definitions);

        void printWordList() const;
        void getWord(const std::string& wordToFind) const;

        void deleteWord(const std::string& word);
        void editWord(const std::string& word, const WordDetails& newDetails);

        // Session persistence
        void setLastWordViewed(const std::string& word);
        std::string getLastWordViewed() const;
    };

    #endif // WORD_MANAGER_HPP