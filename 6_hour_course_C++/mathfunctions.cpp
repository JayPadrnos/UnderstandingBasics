#include <iostream>
#include <cmath>


int main() {
    double x = 3;
    double y = 4;
    double z;

    z = std::max(x, y); // returns greater of two values or variables

    z = std::min(x, y); // returns the lesser of the two values or variables

    // uses the cmath header file

    z = pow(2, 4); // raise a base to a given power

    z = sqrt(9); // square root 

    z = abs(-3); // absolute value

    z = round(x); // rounding function to round a number to the whole number

    z = ceil(x); // rounds a number up with a remainder over a whole number

    z = floor(x); // always rounds down

    std::cout << z;

    return 0;
}

// there is alot more math functions that you may want to look into but go to c++ math functions 