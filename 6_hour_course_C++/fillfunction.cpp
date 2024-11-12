#include <iostream>

int main() {

    // fill() = Fills a range of elements with a spcified value
    //          fill(begin, end, value)

        // std::string foods[10] = {"pizza", "pizza", "pizza", "pizza", "pizza", "pizza", "pizza", "pizza", "pizza", "pizza"};

       /* for(std::string food : foods){
            std::cout << food << '\n';
        }
            */

           const int SIZE = 99;
           std::string foods[SIZE];

           fill(foods, foods + (SIZE/3), "pizza");
           fill(foods + (SIZE/3), foods + (SIZE/3)*2, "hamburger");
           fill(foods +(SIZE/3)*2, foods + SIZE, "hotdog");

           for(std::string food : foods){
            std::cout << food << '\n';
           }
    return 0;
}