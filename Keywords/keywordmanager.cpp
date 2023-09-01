#include <iostream>
#include "keywordmanager.hpp"

void KeywordManager::addKeyword() {
    Keyword keyword;
    std::cout << "Enter keyword: ";
    std::cin >> keyword.word;
    std::cout << "Enter Definition: ";
    std::cin >> keyword.definition;
    // Similar steps for subject, category, and example.
    std::cout << "Enter Subject: ";
    std::cin >> keyword.subject.name;
    std::cout << "Enter Category: ";
    std::cin >> keyword.subject.category.name;
    std::cout << "Enter an Example: ";
    std::cin >> keyword.example.text;
    keywords.push_back(keyword);
}

void KeywordManager::displayKeywords() {
    for (const Keyword& keyword : keywords) {
        std::cout << "Keyword: " << keyword.word << "\n";
        std::cout << "Definition: " << keyword.definition << "\n";
        std::cout << "Subject: " << keyword.subject.name << "\n";
        std::cout << "Category: " << keyword.subject.category.name << "\n";
        std::cout << "Example: " << keyword.example.text << "\n";
    }
}