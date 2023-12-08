// Just for testing

#include <iostream>
using namespace std;

//define a class
class Car {
    public:
        string brand;
        string model;
        int year;
};

int main () {
    //create an object of Car
    Car carObj;
    carObj.brand = "Buick";
    carObj.model = "Lucerne";
    carObj.year = 2006;
    carObj.history = // add a plugin for history or .hpp

    //Print car details
    cout << carObj.brand << " " << carObj.model << " " << carObj.year << carObj.history << endl;
            // outputs: Buick Lucerne 2006
    return 0;
}