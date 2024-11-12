#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    bool canPartition(std::vector<int>& nums) {
        int totalSum = std::accumulate(nums.begin(), nums.end(), 0);
        
        // If the total sum is odd, partition is not possible
        if (totalSum % 2 != 0) {
            return false;
        }

        int target = totalSum / 2;
        std::vector<bool> dp(target + 1, false);
        dp[0] = true;  // Base case: sum of 0 is always possible

        // Update dp array for each number
        for (int num : nums) {
            for (int j = target; j >= num; --j) {
                dp[j] = dp[j] || dp[j - num];
            }
        }

        return dp[target];
    }
};
