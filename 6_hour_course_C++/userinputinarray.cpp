#include <iostream>

int main() {

    std::string foods[5];
    int size = sizeof(foods)/sizeof(foods[0]);
    std::string temp;

    for(int i = 0; i < size; i++){
        std::cout << "Enter a food you like or 'q' to quit #" << i << ": ";
        std::getline(std::cin, foods[i]);
        if(temp == "q"){
            break;
        }
        else{
            foods[i] = temp;
        }
    }

    std::cout << "You like the following food";

    for(int i = 0; !foods[i].empty(); i++){
        std::cout << foods << '\n';
    }

    return 0;
}