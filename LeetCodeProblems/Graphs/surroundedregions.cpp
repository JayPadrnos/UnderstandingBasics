#include <vector>
#include <functional>

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty()) return;
        int rows = board.size();
        int cols = board[0].size();

        // Use a lambda function for DFS
        std::function<void(int, int)> dfs = [&](int x, int y) {
            if (x < 0 || x >= rows || y < 0 || y >= cols || board[x][y] != 'O') return;
            board[x][y] = '#';
            dfs(x + 1, y);
            dfs(x - 1, y);
            dfs(x, y + 1);
            dfs(x, y - 1);
        };

        // Mark the 'O's on the borders and their connected 'O's
        for (int i = 0; i < rows; ++i) {
            if (board[i][0] == 'O') dfs(i, 0);
            if (board[i][cols - 1] == 'O') dfs(i, cols - 1);
        }
        for (int j = 0; j < cols; ++j) {
            if (board[0][j] == 'O') dfs(0, j);
            if (board[rows - 1][j] == 'O') dfs(rows - 1, j);
        }

        // Flip the remaining 'O's to 'X's
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j] == 'O') board[i][j] = 'X';
            }
        }

        // Restore the marked 'O's back to 'O'
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j] == '#') board[i][j] = 'O';
            }
        }
    }
};
