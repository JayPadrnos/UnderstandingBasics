#include "Keywords.hpp"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    KeywordLibrary keywordLibrary;
    
    keywordLibrary.addKeyword("class", "A blueprint for creating objects.", "Programming");
    keywordLibrary.addKeyword("function", "A block of code that performs a specific task.", "Programming");
    keywordLibrary.addKeyword("variable", "A name storage location that holds a value.", "Programming");
    // Add more the more you learn.

    string query;
    char choice;

    const KeywordDefinition* definition = nullptr; // Declare and initialize outside the switch
    optional<KeywordDefinition> definitionOpt;
    vector<KeywordDefinition> categoryKeywords;

    do {
        cout << "Options: \n";
        cout << "1. Print all keywords and definitions\n";
        cout << "2. Get all definitions of a specific keyword\n";
        cout << "3. Search for keywords by category.\n";
        cout << "4. Exit\n";

        cout << "Enter your choice. ";
        cin >> choice;

        if(!cin) {
            //Clear the input buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the newline character from the buffer
        }

        switch (choice) {
            case '1':
                keywordLibrary.printAllKeywords();
                break;
            case '2':
                cout << "Enter the keyword: ";
                getline(cin, query);

                definitionOpt = keywordLibrary.getKeywordDefinition(query);
                if (definitionOpt) {
                    KeywordDefinition definition = *definitionOpt;
                    cout << "Definition: " << definition.definition << "\n";
                } else {
                    cout << "Keyword not found. \n";
                }
                break;
            case '3':
                cout << "Enter the category: ";
                getline(cin, query);

                categoryKeywords = keywordLibrary.getKeywordsByCategory(query);
                if (!categoryKeywords.empty()) {
                    for (const auto &def : categoryKeywords) {
                        cout << "Keyword: " << def.keyword << "\n";
                        cout << "Definition: " << def.definition << "\n";
                        cout << "Category: "  << def.category << "\n";
                        cout << "------------------------------------\n";
                    }
                } else {
                    cout << "NO keywords found in the specified category. \n";
                }
                    break;
            case '4':
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again. \n";
        }
    } while (choice != '4');
    
    return 0;
}

// have a way to save words within the program so that you are able to not only enter new words and descriptions here but also inside the program
