#ifndef KEYWORDS_HPP
#define KEYWORDS_HPP

#include <string>
#include <vector>

using namespace std;

struct KeywordDefinition {
    string keyword;
    string definition;
};

class KeywordLibrary {
    public:
        void addKeyword(const string &keyword, const string &definition);
        const KeywordDefinition* getKeywordDefinition(const string &keyword) const;
        void printAllKeywords() const;

    private:
        vector<KeywordDefinition> definitions;
};

#endif // KEYWORDS_HPP 