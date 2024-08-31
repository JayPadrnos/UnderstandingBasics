#include <vector>
#include <algorithm>

class Solution {
public:
    int longestIncreasingPath(std::vector<std::vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;

        int rows = matrix.size();
        int cols = matrix[0].size();
        std::vector<std::vector<int>> memo(rows, std::vector<int>(cols, 0));
        int maxLen = 0;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                maxLen = std::max(maxLen, dfs(matrix, memo, i, j));
            }
        }
        return maxLen;
    }

private:
    int dfs(const std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& memo, int row, int col) {
        if (memo[row][col] != 0) return memo[row][col];

        int rows = matrix.size();
        int cols = matrix[0].size();
        int maxLen = 1;

        std::vector<std::vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        for (const auto& dir : directions) {
            int newRow = row + dir[0];
            int newCol = col + dir[1];
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && matrix[newRow][newCol] > matrix[row][col]) {
                maxLen = std::max(maxLen, 1 + dfs(matrix, memo, newRow, newCol));
            }
        }

        memo[row][col] = maxLen;
        return maxLen;
    }
};
