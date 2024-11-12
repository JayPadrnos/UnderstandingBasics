#include <iostream>
#include <string>
#include <algorithm>

std::string reverseString(const std::string& s) {
    std::string reversed = s;
    std::reverse(reversed.begin(), reverse.end());
    return reversed;
}

int main() {
    std::string input;
    std::cout << "Enter a string to reverse: ";
    std::getline(std::cin, input);
    std::string output = reverseString(input);
    std::cout << "Reversed string: " << output << std::endl;
    return 0;
}