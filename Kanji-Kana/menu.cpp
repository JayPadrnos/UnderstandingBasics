#include <iostream>
#include "menu.h"

int showMenu() {
    int choice;
    std::cout << "\n==== Mini Japanese Library ====\n";
    std::cout << "1. View Library\n";
    std::cout << "2. Take Quiz\n";
    std::cout << "3. Exit\n";
    std::cout << "Select: ";
    std::cin >> choice;
    return choice;
}
