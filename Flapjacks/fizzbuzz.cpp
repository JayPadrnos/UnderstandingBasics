/**
 * Instructions for the Intended Behavior:
 * 1. Start from 1 up to and including `n`.
 * 2. For each number `i` in this range:
 *    * If `i` is divisible by both 3 and 5, print "FizzBuzz".
 *    * Otherwise, if `i` is divisible by 3, print "Fizz".
 *    * Otherwise, if `i` is divisible by 5, print "Buzz".
 *    * Otherwise, print the number `i` itself.
 * 
 * If “number % 2 === 0”, this is even


 */

#include <iostream>

void fizzBuzz(int n) {
    for (int i = 1; i <= n; ++i) {
        std::cout << "table i = "; std::cout << i; std::cout << "\n";
        if (i % 3 == 0) {            
    std::cout << "Fizz";
        }
        else if (i % 5 == 0) {            
 	std::cout << "Buzz";
        }
        else if (i % 3 == 0 && i % 5 == 0) {              
    std::cout << "FizzBuzz";
    // Swap this else if to the first if and change fizz to an else if
        }
        else {
            std::cout << i;          }
        std::cout << std::endl;
    }
}

int main() {
    fizzBuzz(15);      return 0;
}
