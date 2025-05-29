#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

class Shell {
    private:
        std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> commands;
        fs::path currentPath;

    public:
        Shell() : currentPath(fs::current_path()) {
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

                std::vector<std::string> args;
                std::string arg;
                while (iss >> arg) args.push_back(arg);

                executeCommand(cmd, args);
            }
        }

        private:
            void registerCommands() {
                commands["exit"] = [&](const auto&) {
                    std::cout << "Exiting shell...\n";
                    std::exit(0);
                };

                commands["echo"] = [&](const auto& args) {
                    for (const auto& word : args)
                        std::cout << word << " ";
                    std::cout << "\n";
                };

                commands ["cd"] = [&](const auto& args) {
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
                    logFile << "\n";
                    logFile.close();
                    std::cout << "Logged to shell.log\n";
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
