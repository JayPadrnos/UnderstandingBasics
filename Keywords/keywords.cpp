#include "Keywords.hpp"
#include <iostream>

void KeywordLibrary::addKeyword(const string &keyword, const string &definition, const string &category) {
    KeywordDefinition newDefinition; // Create a new instance to store the keyword and definition
    newDefinition.keyword = keyword;
    newDefinition.definition = definition;
    newDefinition.category = category;

    definitions.push_back(newDefinition); // Use the correct vector name 'definition'
}

void KeywordLibrary::printAllKeywords() const {
    for (const auto &def : definitions) {
        cout << "Keyword: " << def.keyword << "\n";
        cout << "Definition: " << def.definition << "\n";
        cout << "--------------------------\n";
    }
}

optional<KeywordDefinition> KeywordLibrary::getKeywordDefinition(const string &keyword) const {
    for (const auto &def : definitions) {
        if (def.keyword == keyword) {
            return optional<KeywordDefinition>(def);
        }
    }
    return nullopt;
}

vector<KeywordDefinition> KeywordLibrary::getKeywordsByCategory(const string &category) const {
    vector<KeywordDefinition> keywords;

    for (const auto &def : definitions) {
        if (def.category == category) {
            keywords.push_back(def);
        }
    }

    return keywords;
}