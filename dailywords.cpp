#include <iostream>
#include <vector>
#include <random>
#include "wordnet_wrapper.hpp"

int main() {
    // Initialize Wordnet
    int result = initialize_wordnet();
    if (result != 0) {
        std::cerr << "Failed to initialize Wordnet" << std::endl;
        return 1;
    }
    
    // Create a vector to store random words and definitions
    std::vector<std::string> randomWords;

    // Retrieve 10 random words and their definition
    for (int i = 0; i < 10; ++i) {
        const char* randomWord = get_random_word();
        const char* definition = get_word_definition(randomWord);
        randomWords.push_back(randomWord);
        randomWords.push_back(definition);
    }

    // Display the random words and their definition
    for (size_t i = 0; i < randomWords.size(); i += 2) {
        std::cout << "Word: " << randomWords[i] << std::endl;
        std::cout << "Definition: " << randomWords[i + 1] << std::endl;
        std::cout << std::endl;
    }

    // Cleanup Wordnet
    cleanup_wordnet();

    return 0;
}