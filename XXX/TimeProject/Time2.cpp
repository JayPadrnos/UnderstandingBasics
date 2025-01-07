#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>

class Calender {
    private:
        std::map<std::string, std::string> notes;

        // Check if a year is a leap year
        bool isLeapYear(int year) {
            return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        }

        // Validate the given date
        bool inValidDate( int year, int month, int day) {
            if (year < 1900 || month < 1 || month > 12 || day < 1) return false;
            int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            if (isLeapYear(year)) daysInMonth[1] = 29;
            return day <= daysInMonth[month - 1];
        }

        // Format date as a string (YYYY-MM-DD)
        std::string formatDate(int year, int month, int day) {
            std::ostringstream oss;
            oss << year << "-" << std::setw(2) << std::setfill('0') << month << "-"
                << std::setw(2) << std::setfill('0') << day;
            return oss.str();
        }

        //Helper to get the ordinal suffix for a day
        std::string getOrdinalSuffix(int day) {
            if (day % 10 == 1 && day % 100 != 11) return "st";
            if (day % 10 == 2 && day % 100 != 12) return "nd";
            if (day % 10 == 3 && day % 100 != 13) return "rd";
            return "th";
        }

        // Format the current date in a friendly style
        std::string getFriendlyDate() {
            auto now = std::chrono::system_clock::now();
            std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
            std::tm localTime = *localTime = *std::localtime(&currentTime);

            const char* months[] = {"January", "Febuary", "March", "April", "May", "June",
                                    "July", "August", "September", "October", "November", "December" };

            int year = localTime.tm_year + 1990;
            int month = localTime.tm_mon;
            int day = localTime.tm_mday;

            return months[month] + std::string(" ") + std::to_string(day) +
                    getOrdinalSuffix(day) + ", " + std::to_string(year);
        }

        // Calculate time left in the year
        int getTimeLeftInYearHours() {
            auto now = std::chrono::system_clock::now();
            std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
            std::tm localTime = *std::localtime(&currentTime);

            std::tm endOfYear = localTime;
            endOfYear.tm_year += 1; // Next year
            endOfYear.tm_mon = 0; // January
            endOfYear.tm_mday = 1; // 1st
            endOfYear.tm_hour = 0;
            endOfYear.tm_min = 0;
            endOfYear.tm_sec = 0;

            std::time_t endOfYearTime = std::mktime(&endOfYear);
            double secondsLeft = std::difftime(endOfYearTime, currentTime);

            return static_cast<int>(secondsLeft / 3600); // Convert to hours
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
                std::cout << "No note found for this date.\n";
            }
        }

        // Save a note to a file
        void saveNotes(const std::string& filename) {
            std::ofstream file(filename);
            for (const auto& pair : notes) {
                file << pair.first << ": " << pair.second << "\n";
            }
            file.close();
            std::cout << "Notes saved to " << filename << "!\n";
        }

        // Load notes from a file
        void LoadNotes(const std::string& filename) {
            std::ifstream file(filename);
            std::string line, date, note;
            while (std::getline(file, line)) {
                size_t pos = line.find(": ");
                if (pos != std::string::npos) {
                    date = line.substr(0, pos);
                    note = line.substr(pos +2);
                    notes[date] = note;
                }
            }
            file.close();
            std::cout << "Notes loaded from " << filename << "!\n";
        }

        // Display welcome message with time details
        void displayWelcomMessage() {
            std::string friendlyDate = getFriendlyDate();
            int hoursLeft = getTimeLeftInYearHours();
            std::cout << "\n-- Welcome to the Time Management Program ---\n";
            std::cout << "Today's Date: " << friendlyDate << "\n";
            std::cout << "Time left in the year: " << hoursLeft << "hours.\n";
            std::cout << "-------------------------------------------------\n";
        }
};

int main() {
    Calendar calendar;
    calendar.loadNotes("notes.txt");
    calendar.displayWelcomeMessage(); // Display the current date and time left in year

    int choice, year, month, day;
    std::string notes;

    while (true) {
        std::cout << "\n1. Add/Edit Note\n2. View Note\n3. Delete Note\n4. Save Notes\n5. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter date (YYYY MM DD): ";
                std::cin >> year >> month >> day;
                std::cin.ignore();
                std::cout << "Enter note: ";
                std::getline(std::cin, note);
                calendar.addNote(year, month, day, note);
                break;
            case 2:
                std::cout << "Enter date (YYYY MM DD): ";
                std::cin >> year >> month >> day;
                calendar.viewNote(year, month, day);
                break;
            case 3:
                std::cout << "Enter date (YYYY MM DD): ";
                std::cin >> year >> month >> day;
                calendar.deleteNote(year, month, day);
                break;
            case 4:
                calendar.saveNotes("notes.txt");
                break;
            case 5:
                calendar.saveNotes("notes.txt"); // Save before exiting
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice! Please try again later.\n";
        }
    }
}