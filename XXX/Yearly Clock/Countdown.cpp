#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;

void displayCurrentDateTime() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm localTime = *localtime(&currentTime);

    cout << "Current Date and Time: ";
    cout << put_time(&localTime, "%Y - %m - %d      %H:%M:%S") << endl;
}

void displayTimeLeftInYear() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm localTime = *localtime(&currentTime);

    // Get the start of next year
    tm endOfYear = localTime;
    endOfYear.tm_year += 1;
    endOfYear.tm_mon = 0;
    endOfYear.tm_mday = 1;
    endOfYear.tm_hour = 0;
    endOfYear.tm_min = 0;
    endOfYear.tm_sec = 0;

    time_t endOfYearTime = mktime(&endOfYear);

    // Calculate the difference
    double secondsLeft = difftime(endOfYearTime, currentTime);

    // Breakdown the time
    int days = secondsLeft / (24 * 3600);
    secondsLeft -= days * 24 * 3600;
    int hours = secondsLeft / 3600;
    secondsLeft -= hours * 3600;
    int minutes = secondsLeft / 60;
    secondsLeft -= minutes * 60;

    cout << "Time left in the Year:\n";
    cout << "-----------------------------------\n";
    cout << "Days:      " << days << endl;
    cout << "Hours:     " << hours << endl;
    cout << "Minutes:   " << minutes << endl;
    cout << "Seconds:   " << secondsLeft << endl;

    // Total time in different units
    int totalHours = (days * 24) + hours;
    int totalMinutes = totalHours * 60 + minutes;
    long long totalSeconds = static_cast<long long>(totalMinutes) * 60 + static_cast<long long>(secondsLeft);

    cout << "\nTotal Time Left:\n";
    cout << "---------------------------------\n";
    cout << "In Hours:      " << totalHours << endl;
    cout << "In Minutes     " << totalMinutes << endl;
    cout << "In Seconds     " << totalSeconds << endl;
}

int main() {
    cout << "\n--- Year Countdown Program ---\n\n";

    displayCurrentDateTime();
    cout << endl;
    displayTimeLeftInYear();

    return 0;
}