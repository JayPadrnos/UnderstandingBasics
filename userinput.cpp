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

   

    std::cout << "Hello " << name << '\n';
    std::cout << "You are " << age << " years old";

    return 0;
}