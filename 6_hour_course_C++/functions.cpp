#include <iostream>

void happyBirthday(std::string name, int age); // Be sure to declare functions before the main

int main() {

    // function = a block of reusable code

    std::string name = "Axon";
    int age = 29;

    happyBirthday(name, age);

    return 0;
}

// parameters can be renamed within the functions parameters without having to rename it in the declaration of it but it must match within the function
void happyBirthday(std::string birthdayBoi, int age){ // yet you can still define them after the main as long as they are declared before the main
    std::cout << "Happy Birthday to" << birthdayBoi << '\n'; // the name being used is declared outside of the function meaning that the parameter must be defined within the functions () it also must be shown in the declaration of said function 
    std::cout << "You are " << age << "years old";
}