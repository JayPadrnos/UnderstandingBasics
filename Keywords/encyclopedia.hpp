#ifndef ENCYCLOPEDIA_HPP
#define ENCYCLOPEDIA_HPP

#include <string>
#include <vector>
#include <optional>

struct EncyclopediaEntry {
    std::string keyword;
    std::string definition;
    std::string subject;
    std::string category;
    std::string example;
};

class Encyclopedia {
    public:
        void addEntry(const std::string &keyword, const std::string &definition, const std::string &subject, const std::string &category, const std::string &example);
        std::vector<Encyclopedia> getEntriesBySubject(const std::string &subject) const;
        std::optional<Encyclopedia> getEntry(const std::string &keyword) const;
        void printAllEntries() const;

    private:
        std::vector<EncyclopediaEntry> entries;
};

#endif // ENCYCLOPEDIA_HPP