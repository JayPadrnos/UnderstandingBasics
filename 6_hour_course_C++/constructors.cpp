#include <iostream>

class Student{
    public:
        std::string name;
        int age;
        double gpa;

    Student(std::string name, int age, double gpa){    // could have set as Student(std::string x, int y, double z)  name = x age = y gpa =z
    
        this->name = name;
        this->age = age;
        this->gpa = gpa;
    }

};

int main() 
{
            /* constructor = special method that is automatically called when an object is instantiated
            useful for assigning values to attributes as arguments
            */

           Student student1("Spongebob", 25, 3.2);

           std::cout << student1.name;
           std::cout << student1.age;
           std::cout << student1.gpa;

           return 0;
}
