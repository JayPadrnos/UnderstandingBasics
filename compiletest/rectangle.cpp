#include "rectangle.hpp"

// Constructor
Rectangle::Rectangle(double w, double h) : width(w), height(h) {}

// Area Function
double Rectangle::area() const {
    return width * height;
}
