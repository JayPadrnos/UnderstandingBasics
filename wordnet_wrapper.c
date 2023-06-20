#include "wordnet_wrapper..h"
#include <stdio.h>
#include "wordnet.h"

// Function definition for WordNet operations

int initialize_wordnet() {
    return winit();
}

void cleanup_wordnet() {
    wndestroy();
}

const char* get__word(int index) {
    return word[index].word;
}

int get_word_index(const char* word) {
    return lookup_word(word);
}

const char* get_synset_gloss(int index) {
    return synset[index].defn;
}