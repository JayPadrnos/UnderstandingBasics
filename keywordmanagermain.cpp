#include <iostream>
#include "keywordmanager.hpp"

int main() {
    KeywordManager manager;

    int choice;
    do {
        std::cout << "1. Add Keyword\n";
        std::cout << "2. Display Keywords\n";
        std::cout << "3. Exit\n";
        std::cout << "4. Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                manager.addKeyword();
                    break;
            case 2:
                manager.displayKeywords();
                break;
            case 3:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. \n";
        }
    } while (choice != 3);

    return 0;
}