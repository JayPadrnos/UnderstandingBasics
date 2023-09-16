#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Transaction {
    string data;
    string description;
    string category;
    double amount;
    bool isIncome; // True for income False for expense
};

vector<Transaction> transactions;

void addTransaction() {
    // Implement adding a transaction
}

void viewTransaction() {

}

void generateSummaryReport() {

}

void saveToFile() {

}

void loadFromFile() {

}

int main() {
    loadFromFile();

    int choice;
    while (true) {
        cout << "Personal Finance Tracker Menu: " << "\n";
        cout << "1. Add Transaction: " << "\n";
        cout << "2. View Transaction: " << "\n";
        cout << "3. Generate Summary Report: " << "\n";
        cout << "4. Quit" << "\n";
        cout << "5. Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTransaction();
                break;
            case 2:
                viewTransaction();
                break;
            case 3:
                generateSummaryReport();
                break;
            case 4:
                saveToFile();
                return 0;
            default:
                cout << "Invalid choice. Try again." << "\n";
        }
    }

    return 0;
}