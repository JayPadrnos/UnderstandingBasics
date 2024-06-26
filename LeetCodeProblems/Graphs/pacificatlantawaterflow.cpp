#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        // Check for an empty input and return an empty result.
        if (heights.empty() || heights[0].empty()) return {};

        int rows = heights.size();
        int cols = heights[0].size();

        // Create matrices to record reachability to the oceans.
        vector<vector<bool>> pacific_reachable(rows, vector<bool>(cols, false));
        vector<vector<bool>> atlantic_reachable(rows, vector<bool>(cols, false));

        // Perform DFS from the borders of the grid.
        for (int i = 0; i < rows; ++i) {
            dfs(heights, pacific_reachable, i, 0);
            dfs(heights, atlantic_reachable, i, cols - 1);
        }
        for (int j = 0; j < cols; ++j) {
            dfs(heights, pacific_reachable, 0, j);
            dfs(heights, atlantic_reachable, rows - 1, j);
        }

        // Collect cells that can reach both oceans.
        vector<vector<int>> result;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (pacific_reachable[i][j] && atlantic_reachable[i][j]) {
                    result.push_back({i, j});
                }
            }
        }

        return result;
    }

private:
    // Direction vectors for moving in the grid (up, right, down, left).
    const vector<int> direction{-1, 0, 1, 0, -1};

    // Depth-First Search helper function.
    void dfs(vector<vector<int>>& heights, vector<vector<bool>>& reachable, int row, int col) {
        int rows = heights.size();
        int cols = heights[0].size();
        reachable[row][col] = true;

        // Explore the four possible directions.
        for (int k = 0; k < 4; ++k) {
            int newRow = row + direction[k];
            int newCol = col + direction[k + 1];

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                !reachable[newRow][newCol] && heights[newRow][newCol] >= heights[row][col]) {
                dfs(heights, reachable, newRow, newCol);
            }
        }
    }
};
