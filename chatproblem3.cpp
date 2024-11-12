#include <iostream>

using namespace std;

int main() {
    int input1;
    int input2;
    
    cout << "Hello User can you put in a number?" << endl;
    cin >> input1;
    cout << "You have put in " << input1 << "! " << endl;

    cout << "Could you put in another number?" << endl;
    cin >> input2;
    cout << "You have entered in " << input2 << "! " << endl;

    int solution = input1 + input2;
    cout << "The sum of " << input1 << " and " << input2 << " is: " << solution << endl;

    return 0;
}