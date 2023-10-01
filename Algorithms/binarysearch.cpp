#include <iostream>

int binarySearch(int arr[], int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) /2;

        // If the key is at the middle, return the index
        if (arr[mid] == key) {
            return mid;
        }

        // If the key to greater, ignore the left half
        if (arr[mid] < key) {
            left = mid + 1;
        }
        // If the key is smaller, ignore the right half
        else {
            right = mid - 1;
        }
    }

    // Key not found
    return -1;
}

int main() {
    int arr[] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 66;

    int result = binarySearch(arr, 0, n - 1, key);

    if (result != -1) {
        std::cout << "Element found at index " << result << std::endl;
    } else {
        std::cout << "Element not found in the array. \n";
    }

    return 0;
}