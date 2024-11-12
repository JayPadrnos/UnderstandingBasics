#include <iostream>
#include <string>

int main() {
    std::string noun;
    std::string noun2;
    std::string verb;
    std::string adjective;
    std::string preposition;

    std::cout << "Welcome to C++ Mad Libs!\n\n";
    
    std::cout << "Enter a noun: ";
    std::getline(std::cin, noun);

    std::cout << "Enter a second noun: ";
    std::getline(std::cin, noun2);

    std::cout << "Enter a verb: ";
    std::getline(std::cin, verb);

    std::cout << "Enter an adjective: ";
    std::getline(std::cin, adjective);

    std::cout << "Enter a preposition: ";
    std::getline(std::cin, preposition);

    std::cout << "\nHere's your story:\n\n";
    std::cout << "The " << adjective << " " << noun << " " << verb << " " 
    << preposition << " the " << noun2 << ".\n";
    
    return 0;
}