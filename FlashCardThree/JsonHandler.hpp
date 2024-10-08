#ifndef JSONHANDLER_HPP
#define JSONHANDLER_HPP

#include <vector>
#include <nlohmann/json.hpp>

class JsonHandler {
    public:
        static std::vector<nlohmann::json> loadDeckFromFile(const std::string& fileName);
};

#endif