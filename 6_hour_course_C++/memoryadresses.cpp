#include <iostream>

int main() {

    // memory address = a location in memory where the data is stored
    // a memory address can accessed with & (address-of operator)

    std::string name = "Axon";
    int age = 29;
    bool student = true;

    std::cout << &name << '\n';
    std::cout << &age << '\n';
    std::cout << &student << '\n';

    // will be displayed in hexidecimal
    // can convert to decimal to see how much data is used




    return 0;
}