#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthOfLIS(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int n = nums.size();
        std::vector<int> dp(n, 1); // Initialize dp array with 1
        
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }
        
        return *std::max_element(dp.begin(), dp.end()); // Find the maximum length in dp array
    }
};
