#include <vector>


class Solution {
    public:
        bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
            int m = matrix.size();
            int n = matrix[0].size();

            int left = 0;
            int right = m * n - 1;

            while (left <= right) {
                int mid = left + (right - left) / 2;
                int midElement = matrix[mid / n][mid % n]; // Convert 1D index to a 2D matrix index

                if (midElement == target) {
                    return true; // Found the target
                } else if (midElement < target) {
                    left = mid + 1; // Search the right half
                } else {
                    right = mid - 1; // Search the left half
                }
            }

            return false; // Target not found
        }
};