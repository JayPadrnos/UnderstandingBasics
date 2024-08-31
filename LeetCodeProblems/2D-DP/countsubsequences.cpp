class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.length(), n = t.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // Initialization: An empty string t can be formed by any prefix of s
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = 1;
        }

        // Fill dp table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        return dp[m][n];
    }
};
