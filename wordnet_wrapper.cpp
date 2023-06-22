#include "wordnet_wrapper.hpp"
#include <stdio.h>
#include "wn.h"

// Function definition for WordNet operations

int initialize_wordnet() {
    return wninit();
}

void cleanup_wordnet() {
    wndestroy();
}

const char* get_random_word() {
    static char buffer[256];
    int randomIndex = randomsynset();
    sprintf(buffer, "%s", word[randomIndex].word);
    return buffer;
}
 const char* get_word_definition(const char* word) {
    static char buffer[1024];
    int synsetIndex = lookup_word(word);
    sprintf(buffer, "%s", synset[synsetIndex].defn);
    return buffer;
 }