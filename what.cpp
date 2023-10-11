#include <iostream>

int main() {

    std::string choice;

    std::cout << "This all you know?";

    std::cin >> choice;

    if (choice == "yes") {
        std::cout << "Kinda sad dont you think?\n";
    } else if (choice == "no") {
        std::cout << "Oh ho ho than show me.\n";
    } else {
        std::cout << "Invalid choice.\n";
    }

    std::cout << "Kinda sad honestly";

    return 0;

}