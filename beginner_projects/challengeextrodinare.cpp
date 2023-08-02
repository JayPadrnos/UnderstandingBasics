#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

int calculator() {
    int num1, num2;
    char operation;

    cout << "Enter your first number: ";
    cin >> num1;

    cout << "Enter an operator (+, -, *, /): ";
    cin >> operation;
    
    cout << "Enter a second number: ";
    cin >> num2;

    if (operation == '+') {
        cout << "The result is: " << num1 + num2 << endl;
    } else if (operation == '-') {
        cout << "The result is: " << num1 - num2 << endl;
    } else if (operation == '*') {
        cout << "The result is: " << num1 * num2 << endl;
    } else if (operation == '/') {
        if(num2 != 0){
        cout << "The result is: " << num1 / num2 << endl;
    } else {
        cout << "Error Dividing by zero is not allowed" << endl;
      }
    } else {
        cout << "Error! Invalid operator." << endl;
    }

    return 0;
}

int guessgame() {
    srand(static_cast<unsigned int>(time(0)));

    int target = rand() % 10 + 1;
    int guess;
    int lives = 4;

    cout << "Seems youv'e chosen the guessing game. \n";
    cout << "Pretty simple just chose a number between 1 and 10. \n";
    cout << "You have " << lives << " lives remaining \n";

    while (lives > 0) {
        cout << "Enter your guess: ";
        cin >> guess;

        if (guess == target) {
            cout << "Correct guess. \n You win!";
            return 0;
        } else {
            --lives;
            if (lives > 0) {
                cout << "Sorry " << guess << "was incorrect, guess again. \n";
                cout << "You have " << lives << "lives left. \n";
            } else {
                cout << "Sorry " << guess << "was incorrect and you have no lives rmeaining. \n GAME OVER!";
                return 0;
            }
        }
    }

    return 0;
}

int madlibs() {
    string noun;
    string noun2;
    string verb;
    string adjective;
    string preposition;

    cout << "Seems you have chosen madlibs.\n";

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

    cout << "\nHere is your story!\n\n";
    cout << "The " << adjective << " " << noun << " " << verb << " " << preposition << " the " << noun2 << ".\n";

    return 0;
}

int choice_function() {
    int game_to_play;

    cout << "which game would you care to play user 1, 2, or 3? " ;
    cin >> game_to_play;
     
    return game_to_play;
}

int main() {
    int user_input = choice_function();
    
    if (user_input == 1)
        calculator();
    else if  (user_input == 2)
        guessgame();
    else if (user_input == 3)
        madlibs();

    else
    cout << "that seems to be an invalid input.";

    return 0;  
}