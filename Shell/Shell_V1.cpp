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
    std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> commands;
    fs::path currentPath;
    AliasManager aliasManager;

public:
    Shell() : currentPath(fs::current_path()) {
        aliasManager.loadFromFile(".shell_aliases");
        registerCommands();
    }

    void start() {
        std::string input;
        while (true) {
            std::cout << currentPath.string() << "> ";
            std::getline(std::cin, input);

            if (input.empty()) continue;
            std::istringstream iss(input);
            std::string cmd;
            iss >> cmd;

            cmd = aliasManager.resolveAlias(cmd);

            std::vector<std::string> args;
            std::string arg;
            while (iss >> arg) args.push_back(arg);

            executeCommand(cmd, args);
        }
    }

private:
    void registerCommands() {
        commands["exit"] = [&](const auto&) {
            aliasManager.saveToFile(".shell_aliases");
            std::cout << "Aliasers saved.  Exiting shell...\n";
            std::exit(0);
        };

        commands["echo"] = [&](const auto& args) {
            for (const auto& word : args)
                std::cout << word << " ";
        std::cout << "\n";
        };

        commands["cd"] = [&](const auto& args) {
            if (args.empty()) {
                std::cout << "No directory specified.\n";
                return;
            }
            fs::path newPath = args[0];
            if (newPath.is_relative()) newPath = currentPath / newPath;

            if (fs::exists(newPath) && fs::is_directory(newPath)) {
                currentPath = fs::canonical(newPath);
                fs::current_path(currentPath);
            } else {
                std::cout << "Directory not found: " << newPath << "\n";
            }
        };

        commands["pwd"] = [&](const auto&) {
            std::cout << currentPath.string() << "\n";
        };

        commands["help"] = [&](const auto&) {
            std::cout << "Available commands:\n";
            for (const auto& [name, _] : commands) {
                std::cout << "  - " << name << "\n";
            }
        };

        commands["log"] = [&](const auto& args) {
            std::ofstream logFile("shell.log", std::ios::app);
            for (const auto& word : args) logFile << word << " ";
            logfile << "\n";
            logFile.close();
            std::cout << "Logged to shell.log\n";
        };

        commands["alias"] = [&](const auto& args) {
            if (args.size() < 2) {
                aliasManager.listAliases();
                return;
            }
            std::string name args[0];
            std::ostringstream cmd;
            for (size_t i = 1; i < args.size(); ++i) {
                if (i > 1) cmd << " ";
                cmd << args[i];
            }
            aliasManager.setAlias(name, cmd.str());
            std::cout << "Alias set: " << name << "='" << cmd.str() << "'\n";
        };
    }

    void executeCommand(const std::string& cmd, const std::vector<std::string>& args) {
        if (commands.find(cmd) != commands.end()) {
            commands[cmd](args);
        } else {
            std::string fullCommand = cmd;
            for (const auto& arg : args)
                fullCommand += " " + arg;
            std::system(fullCommand.c_str());
        }
    }
};

int main() {
    Shell shell;
    shell.start();
    return 0;
}

// save to file syntaxed