#include <iostream>
#include <ctime>


int main() {

    srand(time(0));
    int randNum = rand() % 5 + 1;

    switch(randNum){
        case 1: std::cout << "You win a bumper sticker";
        break;
        case 2: std::cout << "You win a tshirt";
        break;
        case 3: std::cout << "You win a lunch";
        break;
        case 4: std::cout << "You win a gift card";
        break;
        case 5: std::cout << "You win a concert tickets";
        break;
    }


    return 0;
} 