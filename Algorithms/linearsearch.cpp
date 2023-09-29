#include <iostream>

int linearSearch(int arr[], int n, int key) {
    for (int = 0; i < n; i++) {
        if (arr[i] == key) {
            return i; // element found, return its index
        }
    }
    return -1; // Element not found
}

int main() {
    int arr[] = (10, 45, 67, 89, 34, 56, 78);
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 34;

    int result = linearSearch(arr, n, key);

    if (result != -1) {
        std::cout << "Element found at index " << result << std::endl;
    } else {
        std::cout << "Element not found in the array." << std::endl;
    }

    return 0;
}