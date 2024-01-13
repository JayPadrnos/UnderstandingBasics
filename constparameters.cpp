#include <iostream>

void printInfo(std::string &name, const int &age);



// const parameter = parameter that is effectively read-only
//                  code is more secure & conveys intent
//                  useful for references and pointers


int main() {

    std::string name = "Axon";
    int age = 29;

    printInfo(name, age);

    return 0;
}
void printInfo(const std::string &name, const int &age){
    name = " ";
    age = 0;
    std::cout << name << '\n';
    std::cout << age << '\n';
}