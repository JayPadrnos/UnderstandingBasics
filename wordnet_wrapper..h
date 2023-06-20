#ifndef WORDNET_WRAPPER_H
#define WORDNET_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

// Function declarations for WordNet operations
int initialize_wordnet();
void cleanup_wordnet();
const char* get_word(int index);
int get_word_index(const char* word);
const char* get_synset_gloss(int index);

#ifdef __cplusplus
}
#endif

#endif // WORDNET_WRAPPER_H