#include <iostream>
#include <vector>
using namespace std;

int multiplyAll(const std::vector<int>& arr) {
    int total = 1; 
    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
       
        total *= arr[i];
        std::cout << "This is iteration " << (i + 1) << ", total is " << total; cout << "\n";
        // Pulling to check each variable of the for loop the cout is just a check for the programmer to see the proper data is being captured or not
    }
    return total;
}

int main() {
    std::vector<int> numbers = {2, 5, 7};
    cout << "yup\n";
    int result = multiplyAll(numbers);
    std::cout << "Final result: " << result << std::endl; 
    return 0;
}
