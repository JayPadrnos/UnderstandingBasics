#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        if (grid.empty()) return -1;

        int rows = grid.size();
        int cols = grid[0].size();
        queue<pair<int, int>> q;
        int freshCount = 0;

        // Initialize the queue with all rotten oranges and count the fresh oranges.
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 2) {
                    q.push({r, c});
                } else if (grid[r][c] == 1) {
                    freshCount++;
                }
            }
        }

        // If there are no fresh oranges, return 0.
        if (freshCount == 0) return 0;

        // Directions array for the 4 possible movements (right, down, left, up)
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int minutes = 0;

        // Perform BFS
        while (!q.empty()) {
            int qSize = q.size();
            for (int i = 0; i < qSize; ++i) {
                auto [x, y] = q.front();
                q.pop();

                for (auto [dx, dy] : directions) {
                    int newX = x + dx;
                    int newY = y + dy;

                    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY] == 1) {
                        // Rot the fresh orange
                        grid[newX][newY] = 2;
                        q.push({newX, newY});
                        freshCount--;
                    }
                }
            }

            if (!q.empty()) minutes++;
        }

        // If there are still fresh oranges left, return -1.
        return freshCount == 0 ? minutes : -1;
    }
};
