#include "UserInputHandler.hpp"
#include <iostream>
#include <string>
#include <limits>

UserInputHandler::UserInputHandler(NotesDatabase& _database) : database(_database) {}

void UserInputHandler::startInputLoop() {
    while (true) {
        std::cout << "Choose an option: \n";
        std::cout << "1. Write a note \n";
        std::cout << "2. Read notes\n";
        std::cout << "3. Exit\n";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
            std::cout << "Invalid input. Please enter a number. \n";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue; // Skip the rest of the loop iteration
        }

        if (choice == 1) {
            std::cin.ignore(); // Clear the newline left in the buffer
            std::string title, content;
            std::cout << "Enter title: ";
            std::getline(std::cin, title);
            std::cout << "Enter content: ";
            std::getline(std::cin, content);

            Note newNote(title, content);
            database.addNote(newNote);
        } else if (choice == 2) {
            database.displayAllNotes();
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid choice. Please select a valid option. \n";
        }
    }
}