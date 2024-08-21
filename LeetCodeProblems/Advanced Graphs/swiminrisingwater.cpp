#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> minHeap;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        
        // Start from the top-left corner (0, 0)
        minHeap.push({grid[0][0], 0, 0});
        visited[0][0] = true;
        
        while (!minHeap.empty()) {
            auto [time, x, y] = minHeap.top();
            minHeap.pop();
            
            // If we reached the bottom-right corner, return the time
            if (x == n - 1 && y == n - 1) {
                return time;
            }
            
            // Explore the four directions
            for (const auto& dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                
                if (newX >= 0 && newX < n && newY >= 0 && newY < n && !visited[newX][newY]) {
                    visited[newX][newY] = true;
                    minHeap.push({max(time, grid[newX][newY]), newX, newY});
                }
            }
        }
        
        return -1; // This line should never be reached
    }
};
