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
            if (isLeapYear(year)) dayInMonth[1] = 29;
            return day <= daysInMonth[month - 1];
        }

        // Leap year check
}