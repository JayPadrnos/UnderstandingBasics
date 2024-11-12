#include <iostream>


int myNum = 3; // Global
// Keep in mind using Global variables can pollute the Global namespace and the variables are less secure

void printNum();

int main() {

    // Local variables = declared inside a function or block {}
    // Global variable = declared outside of all function

        int myNum = 1; // Local
        // Local variables are found within a block of code or a function itself

        printNum();

        return 0;

}

void printNum() {
    int myNum = 2;
    std::cout << myNum;
}

// functions will use Local variables first, before resorting to Global variables
// if you want to use a global over a local version you can always precede your variable with (::myNum) in this case