#include <iostream>

int main() {
    // cout << (insertion operator)
    // cin >> (extraction operator)

    std::string name;
    int age;

    std::cout << "What's your age?: ";
    std::cin >> age;

    std:: cout << "What's your name?: ";
    std::getline(std::cin >> std::ws, name);

    // std::ws stands for std white spaces to eliminate the white spaces that would occur allowing you to put something before the input and still read it with the new line

   

    std::cout << "Hello " << name << '\n';
    std::cout << "You are " << age << " years old";

    return 0;
}