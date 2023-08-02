#include <iostream>
#include <string>
using namespace std;

int main() {
    string noun;
    string noun2;
    string verb;
    string adjective;
    string preposition;

    cout << "Welcome to the mad lib experience.\n\n" ;
    
    cout << "Enter a noun: ";
    getline(std::cin, noun);

    cout << "Enter another noun: ";
    getline (std::cin, noun2) ;

    cout << "Enter a verb: ";
    getline(std::cin, verb) ;

    cout << "Enter a adjective: " ;
    getline(cin, adjective) ;

    cout << "Enter a preposition: ";
    getline(cin, preposition) ;

    cout << "\nHere's your story: \n\n";
    cout << "The " << adjective << " " << noun << " " << verb << " "
    << preposition << " the " << noun2 << ".\n";

    return 0 ;
}