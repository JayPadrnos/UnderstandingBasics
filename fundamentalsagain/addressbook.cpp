#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Contact {
    string firstName;
    string lastName;
    string phoneNumber;
    string email;
};

vector<Contact> contacts;

void addContact() {

}

void viewContacts() {

}

void updateContact() {

}

void deleteContact() {

}

void searchContacts() {

}

void saveToFile() {

}

void loadFromFile() {

}

int main() {
    loadFromFile();

    int choice;
    while (true) {
        cout << "Address Book Menu: " << "\n";
        cout << "1. Add Contact: " << "\n";
        cout << "2. View Contacts: " << "\n";
        cout << "3. Update Contacts: " <<  "\n";
        cout << "4. Delete Contacts: " << "\n";
        cout << "5. Search Contacts: " << "\n";
        cout << "6. Quit: " << "\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                updateContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                searchContacts();
                break;
            case 6:
                saveToFile();
                return 0;
            default:
                cout << "Invalid choice. Try again." << "\n";
        }
    }

    return 0;
}