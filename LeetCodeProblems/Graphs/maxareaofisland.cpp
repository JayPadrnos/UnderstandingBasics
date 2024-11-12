#include <vector>
#include <algorithm>

class Solution {
public:
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid) {
        int maxArea = 0;
        int rows = grid.size();
        int cols = grid[0].size();
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1) {
                    int area = dfs(grid, i, j, rows, cols);
                    maxArea = std::max(maxArea, area);
                }
            }
        }
        
        return maxArea;
    }
    
private:
    int dfs(std::vector<std::vector<int>>& grid, int i, int j, int rows, int cols) {
        if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] == 0) {
            return 0;
        }
        
        grid[i][j] = 0;  // mark the cell as visited
        int area = 1;
        
        // explore all 4 possible directions
        area += dfs(grid, i - 1, j, rows, cols);
        area += dfs(grid, i + 1, j, rows, cols);
        area += dfs(grid, i, j - 1, rows, cols);
        area += dfs(grid, i, j + 1, rows, cols);
        
        return area;
    }
};
