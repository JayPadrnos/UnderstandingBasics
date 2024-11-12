#include <iostream>

int main() {

    // int x = 5
    int x; // declaration
    x = 5;

    int y = 6;

    int age = 29;

    // int will only hold whole numbers

    double price = 10.99;

    // double (number including decimal)

    //single character
    char grade = 'A';
    char initial = 'B';
    char dollarSign = '$';

    // boolean (true or false)
    bool student = false;
    bool power = true;
    bool forSale = true;

    // string (object that represents a sequence of text)
    std::string name = "Axon";
    std::string day = "Friday";
    std::string food = "eggs";
    std::string address = "fake street";

    std::cout << "hello " << name << '\n';
    std::cout << "You are " << age << " years old" << '\n';
    std::cout << name;


    std::cout << x << '\n';
    std::cout << y << '\n';


    std::cout << price << '\n';


    return 0;
}