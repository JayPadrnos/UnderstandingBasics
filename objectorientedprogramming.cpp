#include <iostream>

class Human{
    public:
        std::string name;
        std::string occupation;
        int age;

        void eat(){
            std::cout << "This person is eating";
        }
        void drink(){
            std::cout << "This person is drinking";
        }
        void sleep(){
            std::cout << "This person is sleeping";
        }
};

int main(){

    /* object = A collection of attributes and methods 
                They can have charcteristics and could perform actions
                Can be used to mimic real world items (ex. Phone, Book, Dog)
                Created from a class which acts as a "blue-print"
                
    */

   Human human1;

   human1.name = "Rick";
   human1.occupation = "Scientist";
   human1.age = 70;

   std::cout << human1.name;
   std::cout << human1.occupation;
   std::cout << human1.age;

   human1.eat();
   human1.drink();
   human1.sleep();


    return 0;

}