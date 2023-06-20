#include <iostream>
#include <cstdlib>
#include <ctime>
extern "C" {
    #include <wn.h>
}
int main() {
    // Initialize WordNet
    if (!wninit()) {
        std::cerr << "Unable to initialize WordNet" << std::endl;
        return 1;
    }

    // Seed the random number generator
    srand(time(nullptr));

    // Generate and display 10 random words with definitions
    for (int i = 0; i < 10; ++i) {
        int random_sense = rand() % 100 + 1; // Generates random sense number

        // Generate random word
        char word[32];
        snprintf(word, sizeof(word), "n%05d", random_sense); // 'n' indicates noun synset

        // Retrieve synset for the word
        int synset_index = GetWORD(word); // Frustration at its finest
        SynsetPtr synset = GetSynsetForSense(synset_index); // losing my mind here

        if (synset) {
            std::cout << "Word: " << word << std::endl;
            std::cout << "Definition: " << synset->defn << std::endl;
        } else {
            std::cout << "Definition not found for word: " << word << std::endl;
        }
        std::cout << std::endl;
    }
    // Close WordNet
    wnclose(); // and why the hell does this one not work?!?

    return 0;
}