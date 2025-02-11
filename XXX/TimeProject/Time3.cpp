#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime> 
#include <chrono>
#include <stdexcept>
#include <cmath>

class LunarTracker {
    private:
        std::time_t reference_new_moon;
        const double synodic_month = 29.53059;

    public:
        LunarTracker() {
            // Set reference new moon to January 11, 2024 11:57 UTC
            std::tm tm = {};
            tm.tm_year = 2024 - 1900;
            tm.tm_mon = 0; // January (0-based)
            tm.tm_mday = 11;
            tm.tm_hour = 11;
            tm.tm_min = 57;
            reference_new_moon = std::mktime(&tm);
        }

        double getMoonAge(std::time_t date = std::time(nullptr)) {
            double days_since = std::difftime(date, reference_new_moon) / (24 * 3600);
            return std::fmod(days_since, synodic_month);
        }

        std::string getMoonPhase(std::time_t date = std::time(nullptr)) {
            double moon_age = getMoonAge(date);

            if (moon_age < 1.0) return "New Moon";
            if (moon_age < 7.38) return "Waxing Crescent";
            if (moon_age < 8.38) return "First Quarter";
            if (moon_age < 14.76) return "Waxing Gibbous";
            if (moon_age < 15.76) return "Full Moon";
            if (moon_age < 22.14) return "Waning Gibbous";
            if (moon_age < 23.14) return "Last Quarter";
            if (moon_age < 29.53) return "Waning Crescent";
            return "New Moon";
        }

        double getIlluminationPercentage(std::time_t date = std::time(nullptr)) {
            double moon_age = getMoonAge(date);
            double angle = (moon_age / synodic_month) * 2 * M_PI;
            double illumination = (1 + std::cos(angle)) / 2 * 100;
            return std::round(illumination * 10) / 10;
        }
};

class Calendar {
    private:
        std::map<std::string, std::string> notes;
        LunarTracker lunar_tracker;

        // Helper for Lunar cycle
        std::time_t dateToTimet(int year, int month, int day) {
            std::tm tm = {};
            tm.tm_year = year - 1900;
            tm.tm_mon = month - 1;
            tm.tm_mday = day;
            return std::mktime(&tm);
        }

        // Check if a year is a leap year
        bool isLeapYear(int year) {
            return (year % 4 == 0 && year % 100 !=0) || (year % 400 ==0);
        }

        // Validate the given date
        bool isValidDate(int year, int month, int day) {
            if (year < 1900 || month < 1 || month > 12 || day < 1) return false;
            int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
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

        // Helper to get the ordinal suffix for a day
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
            std::tm* localTime = std::localtime(&currentTime);

            const char* months[] = {"January", "February", "March", "April", "May", "June",
                                    "July", "August", "September", "October", "November", "December"};
            
            int year = localTime->tm_year + 1900; // Correct year calculation
            int month = localTime->tm_mon;
            int day = localTime->tm_mday;

            return months[month] + std::string(" ") + std::to_string(day) +
                   getOrdinalSuffix(day) + ", " + std::to_string(year);
        }

        // Calculate time left in the year
        int getTimeLeftInYearHours() {
            auto now = std::chrono::system_clock::now();
            std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
            std::tm* localTime = std::localtime(&currentTime);

            std::tm endOfYear = *localTime;
            endOfYear.tm_mon = 11; // December
            endOfYear.tm_mday = 31; // 31st
            endOfYear.tm_hour = 23;
            endOfYear.tm_min = 59;
            endOfYear.tm_sec = 59;

            std::time_t endOfYearTime = std::mktime(&endOfYear);

            // More precise calculation using chrono
            auto nowChrono = std::chrono::system_clock::now();
            auto endOfYearChrono = std::chrono::system_clock::from_time_t(endOfYearTime);

            auto duration = std::chrono::duration_cast<std::chrono::hours>(
                endOfYearChrono - nowChrono
            );

            return static_cast<int>(duration.count());
        }

    public:
        // Add or edit a note
        void addNote(int year, int month, int day, const std::string& note) {
            if (!isValidDate(year, month, day)) {
                throw std::invalid_argument("Invalid date!");
            }
            std::string date = formatDate(year, month, day);
            notes[date] = note;
            std::cout << "Note added for " << date << "!\n";
        }

        // View note for specific date
        void viewNote(int year, int month, int day) {
            std::string date = formatDate(year, month, day);
            auto it = notes.find(date);
            if (it != notes.end()) {
                std::cout << "Note on " << date << ": " << it->second << "\n";
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
            if (!file) {
                std::cerr << "Error: Unable to open file " << filename << " for writing. \n";
                return;
            }
            for (const auto& pair : notes) {
                file << pair.first << ": " << pair.second << "\n";
            }
            file.close();
            std::cout << "Notes saved to " << filename << "!\n";
        }

        // Load notes from a file
        void loadNotes(const std::string& filename) {
            std::ifstream file(filename);
            if (!file) {
                std::cerr << "No existing notes file found. Starting with empty notes.\n";
                return;
            }

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

        // Lunar Tracker
        void displayMoonInfor(int year, int month, int day) {
            if (!isValidDate(year, month, day)) {
                throw std::invalid_argument("Invalid date!");
            }

            std::time_t date = dateToTimet(year, month, day);
            std::string phase = lunar_tracker.getMoonPhase(date);
            double illumination = lunar_tracker.getIlluminationPercentage(date);
            double age = lunar_tracker.getMoonAge(date);

            std::cout << "\nMoon Information for " << formatDate(year, month, day) << ":\n";
            std::cout << "Phase: " << phase << "\n";
            std::cout << "Moon Age: " << std::fixed << std::setprecision(1) << age << " days\n";
            std::cout << "Illumination: " << illumination << "%\n";
        }

        // Display welcome message with time details
        void displayWelcomeMessage() {
            std::string friendlyDate = getFriendlyDate();
            int hoursLeft = getTimeLeftInYearHours();
            std::cout << "\n-- Welcome to the Time Management Program ---\n";
            std::cout << "Today's Date: " << friendlyDate << "\n";
            std::cout << "Time left in the year: " << hoursLeft << " hours.\n";
            std::cout << "Current Moon Phase: " << lunar_tracker.getMoonPhase() << "\n";
            std::cout << "Moon Illumination: " << lunar_tracker.getIlluminationPercentage() << "%\n";
            std::cout << "------------------------------------------------\n";
        }
};

    int main() {
        Calendar calendar;

        try {
            calendar.loadNotes("notes.txt");
            calendar.displayWelcomeMessage();

            int choice, year, month, day;
            std::string note;

            while (true) {
                std::cout << "\n1.. Add/Edit Note\n2. View Note\n3. Delete Note\n4. Save Notes\n5. View Moon Info\n6. Exit\n";
                std::cout << "Enter choice: ";

                if (!(std::cin >> choice)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a number.\n";
                    continue;
                }

                switch (choice) {
                    case 1:
                        try {
                            std::cout << "Enter date (YYYY MM DD): ";
                            std::cin >> year >> month >> day;
                            std::cin.ignore();
                            std::cout << "Enter note: ";
                            std::getline(std::cin, note);
                            calendar.addNote(year, month, day, note);
                        } catch (const std::invalid_argument& e) {
                            std::cout << "Error: " << e.what() << "\n";
                        }
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
                        std::cout << "Enter date (YYYY MM DD): ";
                        std::cin >> year >> month >> day;
                        try {
                            calendar.displayMoonInfor(year, month, day);
                        } catch (const std::invalid_argument& e) {
                            std::cout << "Error: " << e.what() << "\n";
                        }
                        break;
                    case 6:
                        calendar.saveNotes("notes.txt");
                        std::cout << "Goodbye!\n";
                        return 0;
                    default:
                        std::cout << "Invalid choice! Please try again.\n";
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "An unexpected error occured: " << e.what() << "\n";
            return 1;
        }
    }

    // Add Lunar cycle to this file and program with updated ver compile 3.1
    // Add Temperature of the da as well?

    // AI retrieval system??