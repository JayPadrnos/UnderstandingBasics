#include "JsonHandler.hpp"
#include <fstream>
#include <iostream>

std::vector<nlohmann::json> JsonHandler::loadDeckFromFile(const std::string& fileName) {
    std::vector<nlohmann::json> deckData;
    std::ifstream file(fileName);
    if (file.is_open()) {
        file >> deckData;
        file.close();
    } else {
        std::cerr << "Failed to open file: " << fileName << std::endl;
    }
    return deckData;
}