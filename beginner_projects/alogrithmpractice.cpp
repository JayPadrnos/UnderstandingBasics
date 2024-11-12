#include <iostream>

int main() {
    // Array of numbers 
    int numbers[] = {5, 2, 8, 3, 1};

    // Calculate the length of the array
    int length = sizeof(numbers) / sizeof(numbers[0]);

    // Initialize max with the first element
    int max = numbers[0];

    // Find the max element
    for (int i = 1; i < length; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    // Output the max element
    std::cout << "The maximum number is: " << max << std::endl;

    return 0;
}