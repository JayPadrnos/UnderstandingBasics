#include <iostream>

int main() {



    // ternary operator ?: = replacement to an if/else statement
    // condition ? expression1 : expression2;

    int grade = 75;

    if(grade >= 60){
        std::cout << "You pass!";
    }
    else {
        std::cout << "You fail!";
    }

    grade >= 60 ? std::cout << "You pass!" : std::cout << "You fail!"; // this is the same as writing the previous lines for "if/else" statements

    // remember the modulus (%) gives you the remainder of any division
    int number = 9;
    number % 2 == 1 ? std::cout << "ODD" : std::cout << "EVEN";


    bool hungry = true;

    hungry ? std::cout << "You are hungry" : std::cout << "You are full";

    std::cout << (hungry ? "You are hungry" : "You are full"); // this is another way to write the previous line

    // think of the ? as an "if" and think of the : as an "else"


    return 0;
}