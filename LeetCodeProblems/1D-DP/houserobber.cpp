#include <vector>
#include <algorithm>

class Solution {
public:
    int rob(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        int prev2 = nums[0];
        int prev1 = std::max(nums[0], nums[1]);
        
        for (int i = 2; i < n; ++i) {
            int curr = std::max(prev1, nums[i] + prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};

// Example usage
int main() {
    Solution sol;
    std::vector<int> nums1 = {1, 1, 3, 3};
    std::vector<int> nums2 = {2, 9, 8, 3, 6};
    
    std::cout << sol.rob(nums1) << std::endl; // Output: 4
    std::cout << sol.rob(nums2) << std::endl; // Output: 16
    
    return 0;
}
