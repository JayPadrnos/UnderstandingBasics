#include <iostream>
#include <vector>
using namespace std;


int sumArray(const std::vector<int>& arr) {
    int total = 0;
    
    for  (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        cout << "This is the arr[i], "; cout << arr[i] << "\n";
        total += arr[i];
    }
    return total;
}

int main() {
    std::vector<int> numbers = {2, 5, 7};
    std::cout << "Hello World\n";
    int result = sumArray(numbers);
    std::cout << "Final result: \n" << result << std::endl;
    return 0;
}
