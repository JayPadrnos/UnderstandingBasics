#include "rectangle.hpp"
#include <iostream>

int main() {
    Rectangle rect(5.0, 3.0);
    std::cout << "Area: " << rect.area() << "\n";
    return 0;
}
