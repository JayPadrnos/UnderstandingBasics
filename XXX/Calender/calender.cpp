// Design a calander app that you can put notes on each individual day

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

class Calender {
    private:
        std::map<std::string, std::string> notes;

        bool isValidDate( int year, int month, int day) {
            if (year < 1900 || month < 1 || month > 12 || day < 1) return false;
            int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            if (isLeapYear(year)) daysInMonth[1] = 29;
            return day <= daysInMonth[month - 1];
        }

        // Leap year check
        bool isLeapYear(int year) {
            return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        }

        // Helper to format date as string
        std::string formatDate(int year, int month, int day) {
            std::ostringstream oss;
            oss << year << "-" << std::setw(2) << std::setfill('0') << month << "-"
                << std::setw(2) << std::setfill('0') << day;
            return oss.str();
        }

    public:
        // Add or edit a note
        void addNote(int year, int month, int day, const std::string& note) {
            if (!isValidDate(year, month, day)) {
                std::cout << "Invalid date!\n";
                return;
            }
            std::string date = formatDate(year, month, day);
            notes[date] = note;
            std::cout << "Note added for " << date << "!\n";
        }

        // View note for a specific date
        void viewNote(int year, int month, int day) {
            std::string date = formatDate(year, month, day);
        if (notes.find(date) != notes.end()) {
            std::cout << "Note on " << date << ": " << notes[date] << "\n";
        } else {
            std::cout << "No note for this date.\n";
        }
    }

// Delete a note
void deleteNote(int year, int month, int day) {
    std::string date = formatDate(year, month, day);
    if (notes.erase(date)) {
        std::cout << "Note deleted for " << date << "\n";
    } else {
        std::cout << "No note found for this date. \n";
    }
}

// Save notes to file
void saveNotes(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& pair : notes) {
        file << pair.first << ": " << pair.second << "\n";
    }
    file.close();
    std::cout << "Notes saved to " << filename << "!\n";
}

// Load notes from file
void loadNotes(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, date, note;
    while (std::getline(file, line)) {
        size_t pos = line.find(": ");
        if (pos != std::string::npos) {
            date = line.substr(0, pos);
            note = line.substr(pos + 2);
            notes[date] = note;
        }
    }

    file.close();
    std::cout << "Notes loaded from " << filename << "!\n";
    }
};

int main() {
    Calender calender;
    calender.loadNotes("notes.txt"); // Load notes at startup

    int choice, year, month, day;
    std::string note;

    while (true) {
        std::cout << "/nCalender Note Manageer\n";
        std::cout << "1. Add/Edit Note\n2. View Note\n3. Delete Note\n4. Save Notes\n5. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter date (YYYY MM DD): ";
                std::cin >> year >> month >> day;
                std::cin.ignore();
                std::cout << "Enter note: ";
                std::getline(std::cin, note);
                calender.addNote(year, month, day, note);
                break;
            case 2:
                std::cout << "Enter date (YYYY MM DD): ";
                std::cin >> year >> month >> day;
                calender.viewNote(year, month, day);
                break;
            case 3:
                std::cout << "Enter date (YYYY MM DD): ";
                std::cin >> year >> month >> day;
                calender.deleteNote(year, month, day);
                break;
            case 4:
                calender.saveNotes("notes.txt");
                break;
            case 5:
                calender.saveNotes("notes.txt"); // Save before exiting
                std::cout << "GoodBye!\n";
                return 0;
            default:
                std::cout << "Invalid choice! Please try again. \n";
        }
    }
}