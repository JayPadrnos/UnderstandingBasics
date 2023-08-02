#include <iostream>
#include <string>
using namespace std;
int main() {
    string noun;
    string noun2;
    string verb;
    string adjective;
    string preposition;
    
    cout << "Welcome to C++ Mad Libs!\n\n";
    
    cout << "Enter a noun: ";
    getline(cin, noun);

    cout << "Enter a second noun: ";
    getline(cin, noun2);

    cout << "Enter a verb: ";
    getline(cin, verb);

    cout << "Enter an adjective: ";
    getline(cin, adjective);

    cout << "Enter a preposition: ";
    getline(cin, preposition);

    cout << "\nHere's your story:\n\n";
    cout << "The " << adjective << " " << noun << " "
    << verb << " " << preposition << " the " << noun2 
    << ".\n";
    
    return 0;
}