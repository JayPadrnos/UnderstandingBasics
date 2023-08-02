#include <iostream>

using namespace std;

int main() {
    for (int i = 0; i <= 127; i++) {
        cout << static_cast<char>(i) << " ";
    }

    return 0;
}