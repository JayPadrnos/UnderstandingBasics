#include <iostream>
#include <ctime>

int main() {

    int num;
    int guess;
    int tries;

    srand(time(NULL));
    num = rand() % 100 + 1;

    std::cout << "***** NUMBER GUESSING GAME *******'\n";
    do{
        std::cout << "Enter a guess between 1-100";
        std::cin >> guess;
        tries++;

        if(guess > num){
            std::cout << "Too high!\n";
        }
        else if(guess < num){
            std::cout << "Too low!\n";
        }
        else{
            std::cout << "Correct # of tries " << tries << '\n';
        }
    }while(guess != num);

    std::cout << "**********************************************************";

    return 0;
}

// This code will allow you to guess a number between 1 and 100 until you get the number guessed correct with the alloted number of tries displayed after yuo correctly guess