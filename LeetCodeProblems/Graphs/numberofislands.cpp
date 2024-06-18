#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void dfs(vector<vector<char>>& grid, int i, int j) {
        // Check for boundaries and if the cell is water ('0')
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == '0') {
            return;
        }

        // Mark the cell as visited by setting it to '0'
        grid[i][j] = '0';

        // Visit all adjacent cells (up, down, left, right)
        dfs(grid, i + 1, j); // down
        dfs(grid, i - 1, j); // up
        dfs(grid, i, j + 1); // right
        dfs(grid, i, j - 1); // left
    }

    int numIslands(vector<vector<char>>& grid) {
        int numIslands = 0;

        // Iterate through each cell in the grid
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                // If a cell contains '1', it's a new island
                if (grid[i][j] == '1') {
                    // Perform DFS to mark all connected cells
                    dfs(grid, i, j);
                    // Increment the island count
                    ++numIslands;
                }
            }
        }

        return numIslands;
    }
};

int main() {
    Solution solution;

    vector<vector<char>> grid1 = {
        {'0', '1', '1', '1', '0'},
        {'0', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };

    vector<vector<char>> grid2 = {
        {'1', '1', '0', '0', '1'},
        {'1', '1', '0', '0', '1'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };

    cout << "Number of islands in grid1: " << solution.numIslands(grid1) << endl; // Output: 1
    cout << "Number of islands in grid2: " << solution.numIslands(grid2) << endl; // Output: 4

    return 0;
}
