#include <iostream>
#include <vector>

using namespace std;

int main() {
    int numTerms;
    cout << "Enter the number of terms for the Fibonacci sequence: ";
    cin >> numTerms;

    vector<int> fibonacci;
    fibonacci.push_back(0);
    fibonacci.push_back(1);

    cout << "Fibonacci Sequence: ";

    for (int i = 2; i < numTerms; ++i) {
        int next = fibonacci[i - 1] + fibonacci[i - 2];
        fibonacci.push_back(next);
    }

    for (int term : fibonacci) {
        cout << term << " ";
    }
    cout << endl;

    return 0;
}