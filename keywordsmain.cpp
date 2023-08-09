#include "Keywords.hpp"
#include <iostream>

using namespace std;

int main() {
    KeywordLibrary keywordLibrary;
    
    keywordLibrary.addKeyword("class", "A blueprint for creating objects.");
    keywordLibrary.addKeyword("function", "A block of code that performs a specific task.");
    keywordLibrary.addKeyword("variable", "A name storage location that holds a value.");
    // Add more the more you learn.

    string query;
    char choice;

    const KeywordDefinition* definition = nullptr; // Declare and initialize outside the switch

    do {
        cout << "Options: \n";
        cout << "1. Print all keywords and definitions\n";
        cout << "2. Get all definitions of a specific keyword\n";
        cout << "3. Exit\n";

        cout << "Enter your choice. ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from the buffer

        switch (choice) {
            case '1':
                keywordLibrary.printAllKeywords();
                break;
            case '2':
                cout << "Enter the keyword: ";
                getline(cin, query);

                definition = keywordLibrary.getKeywordDefinition(query); // Assign the value here
                if (definition) {
                    cout << "Definition: " << definition->definition << "\n";
                } else {
                    cout << "Keyword not found. \n";
                }
                    break;
            case '3':
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again. \n";
        }
    } while (choice != '3');
    
    return 0;
}