#ifndef KEYWORD_MANAGER_HPP
#define KEYWORD_MANAGER_HPP

#include <vector>
#include "datastructures.hpp"

class KeywordManager {
    private:
        std::vector<Keyword> keywords;

    public:
        void addKeyword();
        void displayKeywords();
};

#endif // KEYWORD_MANAGER_HPP

