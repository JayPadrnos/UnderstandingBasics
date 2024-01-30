#include <iostream>

int main() {
    // type conversion = conversion a value of one data type to another
    //                  Implicit = automatic
    //                  Explicit = Precede value with new data type (int)

    char x = 100;
    std::cout << x;
    // this would come out to = d from the ASCII table

    std::cout << (char) 100;

    // correct number of questions
    int correct = 8;
    int questions = 10;
    double score = correct/(double)questions * 100;

    std::cout << score << "%";
    // this would output a % of a quiz with 10 questions 8 being correct so it should output 80%
    // as we have specified that questions is a double allowing for the decimal to not be "truncated"

    return 0;
}