#include <iostream>

int main() {
    const int size = 5;
    int arr[size] = {5, 2, 8, 1, 7};

    int max = arr[0];
    int min = arr[0];

    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }

        if (arr[i] < min) {
            min = arr[i];
        }
    }

    std::cout << "Maximum: " << max << std::endl;
    std::cout << "Minimum: " << min << std::endl;

    return 0;
}