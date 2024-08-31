class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int total_sum = 0;
        for(int num : nums) {
            total_sum += num;
        }
        
        // Check if target is achievable
        if (total_sum < abs(target) || (target + total_sum) % 2 != 0) {
            return 0;
        }
        
        int S1 = (target + total_sum) / 2;
        
        // DP array to store the number of ways to achieve each sum
        vector<int> dp(S1 + 1, 0);
        dp[0] = 1;  // There's one way to achieve a sum of 0
        
        for (int num : nums) {
            for (int i = S1; i >= num; i--) {
                dp[i] += dp[i - num];
            }
        }
        
        return dp[S1];
    }
};
