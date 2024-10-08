class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int s = word2.length();
        
        // Create a 2D DP array
        vector<vector<int>> dp(m + 1, vector<int>(s + 1, 0));
        
        // Initialize the first row and first column
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= s; ++j) {
            dp[0][j] = j;
        }
        
        // Fill the DP table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= s; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }
            }
        }
        
        // The answer is in the bottom-right cell of the DP table
        return dp[m][s];
    }
};
