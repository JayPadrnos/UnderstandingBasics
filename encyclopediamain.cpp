#include "Encyclopedia.hpp"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    Encyclopedia encyclopedia;

    encyclopedia.addEntry("class", "A blueprint for creating objects", "Programming", "C++", "N/A");
    // entries added here

    string query;
    char choice;

    optional<EncyclopediaEntry> entryOpt;
    vector<EncyclopediaEntry> subjectEntries;

    do {
        cout << "Options: \n";
        cout << "1. Print all entries\n";
        cout << "2. Get an entry by keyword\n";
        cout << "3. Search for entries by Subject\n";
        cout << "4. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case '1':
                encyclopedia.printAllEntries();
                break;
            case '2':
                cout << "Enter the keyword: ";
                cin.ignore(); // clear the newline character from the buffer
                getline(cin, query);

                entryOpt = encyclopedia.getEntry(query);
                if (entryOpt) {
                    EncyclopediaEntry entry = *entryOpt;
                    cout << "Definition: " << entry.definition << "\n";
                    cout << "Subject: " << entry.subject << "\n";
                    cout << "Category: " << entry.category << "\n";
                    cout << "Example: " << entry.example << "\n";
                } else {
                    cout << "Entry not found. \n";
                }
                break;
            case '3':
                cout << "Enter the subject: ";
                cin.ignore(); // Clear the newline character from the buffer
                getline(cin, query);

                subjectEntries = encyclopedia.getEntriesBySubject(query);
                if (!subjectEntries.empty()) {
                    for (const auto &entry : subjectEntries) {
                        cout << "Keyword: "<< entry.keyword << "\n";
                        cout << "Definition: " << entry.definition << "\n";
                        cout << "Subject: " << entry.subject << "\n";
                        cout << "Category: " << entry.category << "\n";
                        cout << "Example: " << entry.example << "\n";
                        cout << "---------------------------------------------------\n";
                    }
                } else {
                    cout << "No entries were found in the specified subject. \n";
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