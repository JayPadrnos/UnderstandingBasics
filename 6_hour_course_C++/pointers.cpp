#include <iostream>

int main(){

    std::string name = "Axon";
    int age = 29;
    std::string freePizzas[5] = {"pizza1","pizza2","pizza3","pizza4","pizza5"};

    std::string *pName = &name;
    int *pAge = &age;
    std::string *pFreePizzas = freePizzas;

    std::cout << *pName;
    std::cout << *pAge;
    std::cout << *pFreePizzas;

    // pointers = variable that stores a memory address of another variable 
    //              sometimes it's easier to work with an address

    // & address-of operator
    // * dereference operator\

    return 0;
}