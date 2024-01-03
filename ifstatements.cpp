#include <iostream>

int main() {


    int age;

    std::cout << "Enter your age: ";
    std::cin >> age;

    if(age >= 18){
        std::cout << "Welcome to the site!";
    }
    else if(age < 0){
        std::cout << "You have not been born yet!";
    }
    else if(age >= 100){
        std::cout << "You are too old to enter to the site!"; // this needs to be the original if statement as order does matter 
        // if the code was run like this we would get the original if statement vs this written line.
    }
    else{
        std::cout << "You are not old enough to enter.";
    }
    // if statements = do something if a condition is true.
    //                 if not, then don't do it.
    return 0;
}