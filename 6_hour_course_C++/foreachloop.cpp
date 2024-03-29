#include <iostream>

int main() {

    // foreach loop = loop that eases the traversal over an
    //                      iterable data set

    std::string students[] = {"Sponge", "Pat", "Squid", "Sandy"};

    for(std::string student : students){
        std::cout << student << '\n';
    }

    int grades[] = {65, 72, 81, 93};

    for(int grade : grades){
        std::cout << grade << '\n';
    }

    return 0;
}