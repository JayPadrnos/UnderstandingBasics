#include <iostream>
#include "menu.h"
#include "library.h"
#include "quiz.h"

int main() {
    Library lib;  // preload library

    // Display Word of the Day on startup
    lib.displayWordOfTheDay();

    bool running = true;
    while (running) {
        switch (showMenu()) {
            case 1:
                lib.displayAllWords();
                break;
            case 2:
                runQuiz(lib);
                break;
            case 3:
                running = false;
                break;
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }

    std::cout << "Exiting program...\n";
    return 0;
}
