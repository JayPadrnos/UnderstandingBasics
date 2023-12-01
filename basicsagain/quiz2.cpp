#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string toLower(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

bool askQuestion(const string& question, const string& correctAnswer) {
    string userAnswer;
    cout << question << " ";
    cin >> userAnswer;

    userAnswer = toLower(userAnswer);
    string correctAnswerLower = toLower(correctAnswer);

    return userAnswer == correctAnswer;
}

int main() {
    int score = 0;

    if (askQuestion("What is the capitol of France?", "Paris")){
        cout << "Correct!\n";
        score++;
    } else {
        cout << "Incorrect, the correct answer is Paris \n";
    }

    if (askQuestion("How many continents are there?", "7")) {
        cout << "Correct!\n";
        score++;
    } else {
        cout << "Incorrect, the correct answer is 7 \n";
    }

    if (askQuestion("What is the result of 5 + 8", "13")) {
    cout << "Correct\n";
    score++;
    } else {
        cout << "Incorrect, the correct answer is 13. \n";
    }

    cout << "Your final score is: " << score << " out of 3 \n";

    return 0;
}