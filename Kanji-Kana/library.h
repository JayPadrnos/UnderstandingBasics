#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

struct WordEntry {
    std::string kana;
    std::string romaji;
    std::string english;
};

class Library {
public:
    Library();  // Load words
    void displayAllWords() const;
    void displayWordOfTheDay(); // Word of the Day
    const std::vector<WordEntry>& getWords() const;
private:
    std::vector<WordEntry> words;
};

#endif
