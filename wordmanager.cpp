#include "wordmanager.hpp"
#include <thread>

WordManager::WordManger() {
    loadWordData();
    startAutosave();
}

WordManager::WordManger() {
    saveWordData();
}

void WordManager::loadWordData() {
    std::ifstream inputFile(dataFileName);

    if (inputFile.is_open()) {
        std::string word;
        WordDetails details;

        while (inputFile >> word >> details.pronunciation >> details.definitions >> details.wordType >> details.userAdded) {
            addWord(word, details);
        }

        inputFile.close();
    } else {
        std::cout << "Unable to open file for reading. \n";
    }
}

void WordManager:saveWordData() const {
    std::ofstream outputFile(dataFileName);

    if (outputFile.is_open()) {
        for (const auto& entry : wordDatabase) {
            const auto& word = entry.first;
            const auto& details = entry.second;
            outputFile << word << " " << details.pronunciation << " " << details.definitions << " " << details.wordType << " " << details.userAdded << " \n";
        }

        outputFile.close();
    } else {
        std::cout << "Unable to open file for writing. \n";
    }
}

void WordManager::startAutosave() {
    // Start a separate thread for autosave
    std::thread autosaveThread([this]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::minutes(5)); // Autosave every 5 minutes
            autosave();
        }
    });

    autosaveThread.detach(); // Detach thread so it runs independently
}

void WordManager::autosave() {
    saveWordData();
    std::cout << "Autosaved.\n";
}

void WordManager::addWord(const std::string& word, const WordDetails& details) {
    // Find the position to insert the new word alphabetically
    auto it = wordDatabase.begin();
    while (it != wordDatabase.end() && it->first < word) {
        ++it;
    }

    // Insert the new word at the correct position
    wordDatabase.insert(it, std::make_pair(word, details));
}

void WordManager::defineWord(const std::string& word, const std::string& definitions) {
    auto it = wordDatabase.find(word);
    if (it != wordDatabase.end()) {
        it->second.definitions = definitions;
    } else {
        std::cout << "Word not found. \n";
    }
}

void WordManager::addAndDefine(const std::string& word, const WordDetails& details, const std::string& definitions) {
    addWord(word, details);
    defineWord(word, definitions);
}

void WordManager::printWordList() const {
    std::cout << "Word List:\n";
    for (const auto& entry : wordDatabase) {
        const auto& word = entry.first;
        const auto& details = entry.second;

        std::cout << word << " - ";

        if(!details.noun.empty())
            std::cout << "Noun: " << details.noun;
        else if (!details.verb.empty())
            std::cout << "Verb: " << details.verb;
        else if (!details.adjective.empty())
            std::cout << "Adjective: " << details.adjective;

        std::cout << " (" << details.wordType << ") - " << details.definitions;

        if (details.userAdded) {
            std::cout << "  // USER ADDED";
        }

        std::cout << "\n";
    }
}

void WordManager::getWord(const std::string& wordToFind) const {
    auto it = wordDatabase.find(wordToFind);
    if (it != wordDatabase.end()) {
        const WordDetails& details = it->second;
        std::cout << "Word: " << wordToFind << "\n";
        std::cout << "Pronunciation: " << details.pronunciation << "\n";
        std::cout << "Definitions: " << details.definitions << "\n";
        std::cout << "Word Type: " << details.wordType << "\n";
        setLastWordViewed(wordToFind);
    } else {
        std::cout << "Word not found. \n";
    }
}

void WordManager::deleteWord(const std::string& word) {
    auto it = wordDatabase.find(word);
    if (it != wordDatabase.end()) {
        wordDatabase.erase(it);
        setLastWordViewed(""); // Reset last viewed word after deletion
    } else {
        std::cout << "Word not found.\n";
    }
}

void WordManager::editWord(const std::string& word, const WordDetails& newDetails) {
    auto it = wordDatabase.find(word);
    if(it != wordDatabase.end()) {
        it->second = newDetails;
    } else {
        std::cout << "Word not found.\n";
    }
}

void WordManager::setLastWordViewed(const std::string& word) {
    lastWordViewed = word;
}

std::string WordManager::getLastWordViewed() const {
    return lastWordViewed;
}

#endif //WORD_MANAGER_HPP

// main.cpp

#include "wordmanager.hpp"

int main() {
    WordManager wordManager;

    // Example: Adding words during program runtime
    WordManager::WordDetails details1{"pronunciation1", "definitions1", "noun1", "", "", "Noun", true};
    wordManager.addAndDefine("word1", details1, "word1 definitions");

    WordManager::WordDetails details2{"pronunciation2", "definitions2", "", "verb2", "", "Verb", true};
    wordManager.addAndDefine("word2", details2, "word2 definitions");

    // Example: Displaying the word list
    wordManager.printWordList();

    // Example: Getting information about a specific word
    wordManager.getWord("word1");

    // Example: Deleting a word
    wordManager.deleteWord("word2");

    // Example: Editing a word
    WordManager::WordDetails newDetails{"new_pronunciation", "new_definitions", "new_noun", "", "", "Noun", true};
    wordManager.editWord("word1", newDetails);

    // Example: Displaying the updated word list
    wordManager.printWordList();

    return 0;
}