#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solutions;
        vector<string> board(n, string(n, '.'));
        solve(solutions, board, 0, n);
        return solutions;
    }

private:
    void solve(vector<vector<string>>& solutions, vector<string>& board, int row, int n) {
        if (row == n) {
            solutions.push_back(board);
            return;
        }
        
        for (int col = 0; col < n; ++col) {
            if (isSafe(board, row, col, n)) {
                board[row][col] = 'Q';
                solve(solutions, board, row + 1, n);
                board[row][col] = '.';
            }
        }
    }
    
    bool isSafe(vector<string>& board, int row, int col, int n) {
        // Check the column
        for (int i = 0; i < row; ++i) {
            if (board[i][col] == 'Q') {
                return false;
            }
        }
        
        // Check the upper-left diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        
        // Check the upper-right diagonal
        for (int i = row, j = col; i >= 0 && j < n; --i, ++j) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        
        return true;
    }
};

int main() {
    Solution solution;
    int n = 4; // You can change this value to test with different values of n
    vector<vector<string>> solutions = solution.solveNQueens(n);
    
    for (const auto& solution : solutions) {
        for (const auto& row : solution) {
            cout << row << endl;
        }
        cout << endl;
    }
    
    return 0;
}
