#include <iostream>
using namespace std;

// Define a class
class Dog {
    private: 
        string name; 
        int age;
        int health;
    public: // access specifier
        Dog(const string& dogName, int dogAge, int dogHealth) {
            name = dogName;
            age = dogAge;
            health = dogHealth;
        }

        //method
        void bark() {
            cout << name << "says woof!" << endl;
        }

        void introduction() {
            cout << name << " Says:" "High Ho I am.\n\n";
        }

        void play() {
            cout << name << "Plays with the ball you throw. \n\n";
        }

        void damage() {
            cout << health << endl;
            health--;
            cout << health << endl;
        }

};

int main() {
    Dog Kea("Kea ", 16, 20);
    Dog Buddy("Buddy ", 10, 30);

    Kea.bark();
    Kea.introduction();
    
    Buddy.introduction();
    Buddy.damage();

    return 0;

}