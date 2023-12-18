#include <iostream>

int main() {
    int month, year;
    std::cout << "Enter month (1-12): ";
    std::cin >> month;

    std::cout << "Enter the year: ";
    std::cin >> year;

    int days;

    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7: 
        case 8:
        case 10:
        case 12:
            days = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days = 30;
            break;
        case 2:
            // Check for leap year
            if ((year % 4 == 0 && year % 100 !=0 ) || (year % 400 == 0)) {
                days = 29;
            }
            break;
        default:
            std::cout << "Invalid month" << std::endl;
            return 1;
    }

    std::cout << "Number of days: " << days << std::endl;

    return 0;
}