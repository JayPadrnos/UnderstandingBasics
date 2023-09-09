#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void openFile(const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open the file: " << filename << endl;
    }
}

void editFile(const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        cout << "Enter the text you want to write too the file (press Ctrl+D to save and exit):\n";
        string line;
        while (getline(cin, line)) {
            file << line << endl;
        }
        file.close();
        cout << "File '" << filename << "' has been edited and saved." << endl;
    } else {
        cout << "Unable to open the file: " << filename << endl;
    }
}

int main() {
    while (true) {
        cout << "\nOptions:" << endl;
        cout << "1. Open a text file" << endl;
        cout << "2. Edit a text file" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1/2/3): ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            string filename;
            cout << "Enter the name of the file you want to open: ";
            cin >> filename;
            openFile(filename);
        } else if (choice == 2) {
            string filename;
            cout << "Enter the name of the file you want to edit: ";
            cin >> filename;
            cin.ignore();
            editFile(filename);
        } else if (choice == 3) {
            cout << "Exiting the text editor. " << endl;
            break;
        } else {
            cout << "Invalid choice. Please select 1, 2, or 3. " << endl;
        }
    }

    return 0;
}

// the ctrl + D doesnt work properly to save new text into the .txt