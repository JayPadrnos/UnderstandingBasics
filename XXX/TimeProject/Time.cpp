#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

class Calender {
    private:
        std::map<std::string, std::string> notes;

        // Helper to calculate time left in the year
        std::string calculateTimeLeftInYear() {
            auto now = std::chrono::system_clock::now();
            time_t currentTime = std::chrono::system_clock::to_time_t(now);
            tm localTime = *localtime(&currentTime);

            // Get the start of the next year
            tm endOfYear = localTime;
            endOfYear.tm_year += 1;
            endOfYear.tm_mon = 0;
            endOfYear.tm_mday =1;
            endOfYear.tm_hour = 0;
            endOfYear.tm_min = 0;
            endOfYear.tm_sec = 0;

            time_t endOfYearTime = mktime(&endOfYear);

            // Calculate the difference
            double secondsLeft = difftime(endOfYearTime, currentTime);
            int days = secondsLeft / (24 * 3600);
            secondsLeft -= days * 24 * 3600;
            int hours = secondsLeft / 3600;
            secondsLeft -= hours * 3600;
            int minutes = secondsLeft / 60;

            // Format the remaining time as a string
            std::ostringstream oss;
            oss << "Time left in year: " << days << "days, " << hours << " hours, "
                << minutes << " minutes, " << static_cast<int>(secondsLeft) << " seconds. ";
            return oss.str();
        }

        // Helper to format date as string
        std::string formatDate(int year, int month, int day) {
            std::ostringstream oss;
            oss << year << "-" << std::setw(2) << std::setfill('0') << month << "-"
                << std::setw(2) << std::setfill('0') << day;
            return oss.str();
        }

        bool isValidDate(int year, int month, int day) {
            if (year < 1990 || month < 1 || month > 12 || day < 1) return false;
            int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            if (isLeapYear(year)) daysInMonth[1] = 29;
            return day <= daysInMonth[month - 1];
        }

        bool isLeapYear(int year) {
            return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        }

    public:
        void addNote(int year, int month, int day, const std::string note) {
            if (!isValidDate(year, month, day)) {
                std::cout << "Invalid date\n";
                return;
            }
            std::string date = formatDate(year, month, day);
            std::string timestamp = calculateTimeLeftInYear();
            notes[date] = note + " [" + timestamp + "]";
            std::cout << "Note added for " << date << "!\n";
        }

        void viewNote(int year, int month, int day) {
            std::string date = formatDate(year, month, day);
            if (notes.find(date) != notes.end()) {
                std::cout << "Note on " << date << ": " << notes[date] << "\n";
            } else {
                std::cout << "No note for this date.\n";
            }
        }

        void deleteNote (int year, int month, int day) {
            std::string date = formatDate(year, month, day);
            if (notes.erase(date)) {
                std::cout << "Note deleted for " << date << "\n";
            } else {
                std::cout << "No note found for this date.\n";
            }
        }

        void saveNotes(const std::string& filename) {
            std::ofstream file(filename);
            for (const auto& pair : notes) {
                file << pair.first << ": " << pair.second << "\n";
            }
            file.close();
            std::cout << "Notes saved to " << filename << "!\n";
        }

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
            calender.loadNotes("notes.txt");

            int choice, year, month, day;
            std::string note;

            while (true) {
                std::cout << "\n Calender Note Manager\n";
                std::cout << "1. Add/Edit Note\n2. View Note\n3. Delete Note\n4. Save Note\n5. Exit\n";
                std::cout << "Enter choice: ";
                std::cin >> choice;

                switch(choice) {
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
                    calender.saveNotes("notes.txt");
                    std::cout << "Goodbye!\n";
                    return 0;
                defualt:
                    std::cout << "Invalid choice! Please try again.\n";
                }
            }
        }


// ways to add multiple notes to the program where you can view multiple notes for each day in numbered order
// add a way for notes to be sorted into levels of urgency/importance
// when at complete state have a voice recording button to add notes to days, and even choose days to add said note to
// Daily habit reminder
// Keep track of time on certain apps (runtime)
// List daily habit reminders