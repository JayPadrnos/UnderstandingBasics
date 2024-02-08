#include <iostream>
#include "dictionary.hpp"

int main()
{
    Dictionary dictionary;

    // Words to be added here
    dictionary.addWord("apple", "noun", {"apel"}, {"A fruit"});

    // Main loop
    while (true) {
        std::string input;
        std::cout << "Enter '1', '5', or '10' to get 1, 5, or 10 random words, or quit to exit: ";
        std::cin >> input;

        if (input == "quit") {
            break;
        }

        int count = std::stoi(input);
        if (count == 1 || count == 5 || count == 10) {
            std::vector<Word> randomWords = dictionary.getRandomWords(count);
            for (const auto& word : randomWords) {
                std::cout << "Word: " << word.word << std::endl;
                std::cout << "Type: " << word.type << std::endl;
                std::cout << "Pronunciation: ";
                for (const auto& pronunciation : word.pronunciation) {
                    std::cout << pronunciation << ", ";
                }
                std::cout << std::endl;
                std::cout << "Definition(s): ";
                for (const auto& definition : word.definitions) {
                    std::cout << definition << std::endl;
                }
                std::cout << std::endl;
            }
        } else {
            std::cout << "Invalid input. Please enter '1', '5', or '10'. " << std::endl;
        }
    }

    return 0;
}