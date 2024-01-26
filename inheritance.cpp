#include <iostream>

class Animal{
    public:
        bool alive = true;
    void eat(){
        std::cout << "this animal is eating";
    }
};

class Dog : public Animal{
    public:

    void bark(){
        std::cout << "The dog goes woof";
    }
};

class Cat : public Animal{
    public:

    void meow(){
        std::cout << "The cat goes meow";
    }
}

int main(){

    // inheritance = A class can recieve attributes and methods from another class
    //              Children classes inherit from a Parent class
    //              Helps to reuse similar code found within multiple classes

    Dog dog;

    std::cout << dog.alive;
    dog.eat();
    dog.bark();

    std::cout << cat.alive;
    cat.eat();
    cat.meow();

    return 0;
}