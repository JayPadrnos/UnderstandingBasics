#include <vector>
#include <queue>
#include <utility>

using namespace std;

class Solution {
public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        if (grid.empty()) return;
        
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        
        // Initialize the queue with all treasure chest positions
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }
        
        // Directions array for traversing up, down, left, right
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        // Perform BFS from each treasure chest
        while (!q.empty()) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            
            for (const auto& dir : directions) {
                int newRow = row + dir.first;
                int newCol = col + dir.second;
                
                // If the new position is within bounds and is an unvisited land cell
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n && grid[newRow][newCol] == 2147483647) {
                    // Update the distance and add the cell to the queue
                    grid[newRow][newCol] = grid[row][col] + 1;
                    q.push({newRow, newCol});
                }
            }
        }
    }
};
