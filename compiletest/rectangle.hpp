#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
    Rectangle(double w, double h);
    double area() const;

private:
    double width, height;
};

#endif
