#ifndef WORDNET_WRAPPER_HPP
#define WORDNET_WRAPPER_HPP

extern "C" {

    // Funtion declarations for the WordNet operations
    int initialize_wordnet();
    void cleanup_wordnet();
    const char* get_random_word();
    const char* get_word_definition();

}

#endif // WORDNET_WRAPPER_HPP