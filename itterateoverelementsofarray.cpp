#include <iostream>

int main() {

    std::string students[] = {"Sponge", "Pat", "Squid", "Sandy"};

    char grades[] = {'A', 'B', 'C', 'D', 'F'};

    for(int i = 0; i < sizeof(students)/sizeof(std::string); i++){
        std::cout << students[i] << '\n';
    }
    std::cout << students[0] << '\n'; // Sponge
    std::cout << students[1] << '\n'; // Pat
    std::cout << students[2] << '\n'; // Squid


    for(int i = 0; i < sizeof{grades}/sizeof(char); i++){
        std::cout << grades[i] << '\n';
    }

    return 0;
}