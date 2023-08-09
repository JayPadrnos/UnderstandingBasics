#include "Keywords.hpp"
#include <iostream>

void KeywordLibrary::addKeyword(const string &keyword, const string &definition) {
    KeywordDefinition newDefinition; // Create a new instance to store the keyword and definition
    newDefinition.keyword = keyword;
    newDefinition.definition = definition;

    definitions.push_back(newDefinition); // Use the correct vector name 'definition'
}

void KeywordLibrary::printAllKeywords() const {
    for (const auto &def : definitions) {
        cout << "Keyword: " << def.keyword << "\n";
        cout << "Definition: " << def.definition << "\n";
        cout << "--------------------------\n";
    }
}

const KeywordDefinition* KeywordLibrary::getKeywordDefinition(const string &keyword) const {
    for (const auto &def : definitions) {
        if (def.keyword == keyword) {
            return &def;
        }
    }
    return nullptr;
}