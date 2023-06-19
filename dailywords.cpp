#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wn.h>

int main() {
    // Initialize WordNet
    if (!wninit()) {
        fprintf(stderr, "UNable to initialize WordNet\n");
        return 1;
    }

    // Seed the random number generator
    srand(time(NULL));

    // Generate and display 10 random words with definitions
    for (int i = 0; i < 10; ++i) {
        int random_sense = rand() % 100 + 1; // Generates random sense number

        // Generate random word
        char word[32];
        snprintf(word, sizeof(word), "n%05d", random_sense); // 'n' indicates noun synset
        
        // Retrive synset for the word
        int synset_index = wngetindex(word);
        SynsetPtr synset = wngetsynset(syneset_index);

        if (synset) {
            printf("Word: %s\n", word);
            printf("Definition: %s\n", synset>defn);
        } else {
            printf("Definition not found for word: %s\n", word);
        }
        printf("\n");
    }

    // Close wordnet
    wnclose();
}