#include <iostream>
#include <vector>

int sumGreaterThanFive(const std::vector<int>& arr) {
    int total = 0;
    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        std::cout << "This is iteration, "; std::cout << (i+1); std::cout << "\n"; std::cout << "This is total, "; std::cout << total; std::cout << "\n";
        if (arr[i] > 5) {
            total += arr[i];
             
        }
    }
    return total;
}

int main() {
    std::vector<int> numbers = {10, 2, 15};
    int result = sumGreaterThanFive(numbers);
    std::cout << "Final result: " << result << std::endl;
    return 0;
}
