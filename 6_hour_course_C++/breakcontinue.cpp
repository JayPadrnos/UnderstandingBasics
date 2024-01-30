#include <iostream>

int main() {

    // break = break out of a loop
    // continue = skip current iteration

    for(int i = 1; i <= 20; i++){
        if(i == 13){
            break; // this will stop the loop and break out of it
            continue; // this will continue the loop after skipping 13 in this case
        }
            std::cout << i << '\n';

    }

    return 0;
}