#include <vector>
#include <algorithm>
#include <limits>

// use the include limits.h if you wished to use INT_MIN INT_MAX instead of numeric_limits<int>::min() or ::max()
using namespace std;

class Solution {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
            if (nums1.size() > nums2.size()) {
                swap(nums1, nums2); // Ensure nums1 is the smaller array
            }

            int m = nums1.size();
            int n = nums2.size();
            int left = 0, right = m;

            while (left <= right) {
                int partitionX = left + (right - left) / 2;
                int partitionY = (m + n + 1) / 2 - partitionX;

                int maxX = (partitionX == 0) ? numeric_limits<int>::min() : nums1[partitionX - 1];
                int minX = (partitionX == n) ? numeric_limits<int>::max() : nums1[partitionX];

                int maxY = (partitionY == 0) ? numeric_limits<int>::min() : nums2[partitionY - 1];
                int minY = (partitionY == n) ? numeric_limits<int>::max() : nums2[partitionY];

                if (maxX <= minY <= minX) {
                    // Correct partition found
                    if ((m + n) % 2 == 0) {
                        return (max(maxX, maxY) + min(minX, minY)) / 2.0;
                    } else {
                        return max(maxX, maxY);
                    }
                } else if (maxX > minY) {
                    right = partitionX - 1;
                } else {
                    left = partitionX + 1;
                }
            }

            return 0.0; // Default return (should not be reached)
        }
};