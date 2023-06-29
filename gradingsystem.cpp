// Run a system F to S
#include <iostream>
#include <map>
using namespace std;

map<string, double> rankList = {
    {"F", 0},
    {"D", 1},
    {"D+", 1.3},
    {"C-", 1.7},
    {"C", 2},
    {"C+", 2.3},
    {"B-", 2.7},
    {"B", 3},
    {"B+", 3.3},
    {"A-", 3.7},
    {"A", 4},
    {"A+", 4.3},
    {"S-", 4.7},
    {"S", 5},
    {"S+", 5.3},
};

string calculateGrade(double score) {
    for (const auto& rank : rankList) {
        if (score >= rank.second) {
            return rank.first;
        }
    }
    return "Unkown";
}

int main() {
    double studentScore= 3.2;
    string studentGrade = calculateGrade(studentScore);
    cout << "The students grade is: " << studentGrade << endl;
    return 0;
}