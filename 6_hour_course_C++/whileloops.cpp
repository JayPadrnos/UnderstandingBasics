#include <iostream>

int main() {


        // while loops are kind of like an if statement except can repeat code infinitely as long as condition remains true
        // want a condition to exit the loop otherwise you will get stuck in an infinite loop
    std::string name;

    while(name.empty()){
        std::cout << "Enter your name";
        std::getline(std::cin, name);
    }

    std::cout << "Hello " << name;

    return 0;
}