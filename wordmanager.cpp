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

