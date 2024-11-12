#include <vector>
#include <algorithm>

class Solution {
public:
    int maxCoins(std::vector<int>& nums) {
        int n = nums.size();
        // Add padding with 1 on both ends
        std::vector<int> nums_padded(n + 2, 1);
        for (int i = 0; i < n; ++i) {
            nums_padded[i + 1] = nums[i];
        }

        // Create a DP table
        std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 2, 0));

        // Fill the DP table
        for (int length = 1; length <= n; ++length) {
            for (int i = 1; i <= n - length + 1; ++i) {
                int j = i + length - 1;
                for (int k = i; k <= j; ++k) {
                    int coins = nums_padded[i - 1] * nums_padded[k] * nums_padded[j + 1];
                    coins += dp[i][k - 1] + dp[k + 1][j];
                    dp[i][j] = std::max(dp[i][j], coins);
                }
            }
        }

        return dp[1][n];
    }
};
