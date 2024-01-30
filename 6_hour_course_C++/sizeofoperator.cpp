#include <iostream>

int main() {

    // sizeof() = determines the size in bytes of a :
    //            variable, data type, class, objects, etc.

    std::string name = "Axon";
    double gpa = 2.5;
    char grade = 'F';
    bool student = true;
    char grades[] = {'A', 'B', 'C', 'D', 'F'};

    std::string students[] = {"Sponge", "Pat", "Squid"};

    std::cout << sizeof(grades)/sizeof(char) << "elements\n";

    return 0;
}