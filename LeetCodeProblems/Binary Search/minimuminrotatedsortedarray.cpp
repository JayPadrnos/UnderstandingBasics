#include <vector>
using namespace std;

class Solution {
    public:
        int findMin(vector<int>& nums) {
            int left = 0, right = nums.size() - 1;

            // Binary search to find the minimum element
            while (left < right) {
                int mid = left + (right - left) / 2;

                // Check if mid is the min element
                if (mid > 0 && nums[mid] < nums[mid - 1])
                    return nums[mid];

                if (nums[mid] > nums[right])
                    left = mid + 1;
                else
                    right = mid;
            }

            // At the end of the loop, left and right will converge and nums[left] will be the min
            return nums[left];
        }
};