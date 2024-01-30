#include <iostream>

// The "const" keyword specifies that a variable's value is constant
// tells the compiler to prevent anything from modifying it 
// (read-only)

int main() {
    const double PI = 3.14159;
    double radius = 10;
    double circumfrance = 2 * PI * radius;

    std::cout << circumfrance << "cm";

    return 0;
}