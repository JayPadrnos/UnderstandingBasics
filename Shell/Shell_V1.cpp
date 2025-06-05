#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <cstdlib>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class AliasManager {
private:
    std::unordered_map<std::string, std::string> aliasMap;

public:
    void setAlias(const std::string& name, const std::string& command) {
        aliasMap[name] = command;
    }

    std::string resolveAlias(const std::string& name) const {
        auto it = aliasMap.find(name);
        return (it != aliasMap.end()) ? it->second : name;
    }

    void listAlias() const { 
        for (const auto& [key, value] : aliasMap) {
            std::cout << "alias " << key << "='" << value << "'\n";
        }
    }

    void saveToFIle(const std::string& filename) const {
        std::ofstream outFile(filename);
        for (const auto& [name, cmd] : aliasMap) {
            outFile << name << "=" << cmd << "\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        std::string line;
        while (std::getline(inFile, line)) {
            auto pos = line.find('=');
            if (pos != std::string::npos) {
                std::string name = line.substr(0, pos);
                std::string cmd = line.substr(pos + 1);
                aliasMap[name] = cmd;
            }
        }
    }
};

class Shell {
private:
    std::
}