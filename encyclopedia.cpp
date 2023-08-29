#include "encyclopedia.hpp"
#include <iostream>

void Encyclopedia::addEntry(const std::string &keyword, const std::string &definition, const std::string &subject, const std::string &category, const std::string &example) {
    EncyclopediaEntry newEntry;
    newEntry.keyword = keyword;
    newEntry.definition = definition;
    newEntry.subject = subject;
    newEntry.category = category;
    newEntry.example = example;

    entries.push_back(newEntry);
}

void Encyclopedia::printAllEntries() const {
    for (const auto &entry : entries) {
        std::cout << "Keyword: " << entry.keyword << "\n";
        std::cout << "Definition: " << entry.definition << "\n";
        std::cout << "Subject: " << entry.subject << "\n";
        std::cout << "Category: " << entry.category << "\n";
        std::cout << "Example: " << entry.example << "\n";
        std::cout << "------------------------------------------------------";
    }
}

std::optional<Encyclopedia> Encyclopedia::getEntry(const std::string &keyword) const {
    for (const auto &entry : entries) {
        if (entry.keyword == keyword) {
            return std::optional<EncyclopediaEntry>(entry);
        }
    }
    return std::nullopt;
}

std::vector<EncyclopediaEntry> Encyclopedia::getEntriesBySubject(const std::string &subject) const {
std::vector<EncyclopediaEntry> subjectEntries;

    for (const auto &entry :entries) {
        if (entry.subject == subject) {
            subjectEntries.push_back(entry);
        }
    }

    return subjectEntries;
}