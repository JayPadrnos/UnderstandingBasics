#include <iostream>

int main() {


    std::string name;

    std::cout << "Enter your name";
    std::getline(std::cin, name);

    name.erase(0, 3); // Erase from appointed number to another appointed number for character placement

    std::cout << name;

    std::cout << name.find( ' ' );

    name.insert(0, "@"); // would insert an @ at the position listed in this case 0 would be the start

    std::cout << name;

    std::cout << name.at(1); // wouuld display the character or rather what ever is positioned at 1

    name.append("@gmail.com"); // Adds to the end of said variable or rather appends it to
    
    std::cout << "Your user name is now " << name;

    name.clear();

    std::cout << "Hello " << name;

    if(name.empty()){
        std::cout << "You didn't enter your name";
    }
    else{
        std::cout << "Hello " << name;
    }

    if(name.length() > 12) {
        std::cout << "Your ranem can't be over 12 characters long: ";
    }
    else {
        std::cout << "Welcome " << name;
    }

    return 0;
} 