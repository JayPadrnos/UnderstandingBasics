#include <iostream>

int main() {
    int grade;
    std::cout << "Enter the numerical grade: ";
    std::cin >> grade;

    switch (grade / 10) {
        case 10:
        case 9:
            std::cout << "A" << std::endl;
            break;
        case 8:
            std::cout << "B" << std::endl;
            break;
        case 7:
            std::cout << "C" << std::endl;
            break;
        case 6:
            std::cout << "D" << std::endl;
            break;
        default:
            std::cout << "F" << std::endl;
    }
    
    return 0;
}