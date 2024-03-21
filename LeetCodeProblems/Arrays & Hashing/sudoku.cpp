#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
    public:
        bool isValidSudoku(vector<vector<char>>& board) {
            // Check rows
            for (int i = 0; i < 9; ++i) {
                if (!isValidGroup(board[i]))
                    return false;
            }

            // Check columns
            for (int j = 0; j <9; ++j) {
                vector<char> col;
                for (int i = 0; i < 9; ++i) {
                    col.push_back(board[i][j]);
                }
                if (!isValidGroup(col))
                    return false;
            }

            // Check 3x3 
            for (int i = 0; i < 9; i +=3) {
                for (int j = 0; j < 9; j += 3) {
                    vector<char> subgrid;
                    for (int k = i; k < i + 3; ++k) {
                        for (int l = j; l < j + 3; ++l) {
                            subgrid.push_back(board[k][l]);
                        }
                    }
                    if (!isValidGroup(subgrid))
                        return false;
                }
            }

            return true;
        }

        private:
            bool isValidGroup(const vector<char>& group) {
                unordered_set<char> seen;
                for(char ch : group) {
                    if (ch != '.' && seen.find(ch) != seen.end())
                        return false;
                    seen.insert(ch);
                }
                return true;
            }
};