#include <vector>
#include <string>
#include <stack>

class Solution {
    public:
        std::vector<std::string> generateParenthesis(int n) {
            std::vector<std::string> result;
            std::stack<char> parentheses;
            generateParenthesisRecursive("", n, n, parentheses, result);
            return result;
        }

    private:
        void generateParenthesisRecursive(std::string current, int open, int close, std::stack<char>& parentheses, std::vector<std::string> & result) {
            if (open == 0 && close == 0) {
                result.push_back(current);
                return;
            }

            if (open > 0) {
                parentheses.push('(');
                generateParenthesisRecursive(current + '(', open - 1, close, parentheses, result);
                parentheses.pop();
            }

            if (close > open && !parentheses.empty()) {
                parentheses.pop();
                generateParenthesisRecursive(current + ')', open, close - 1, parentheses, result);
                parentheses.push('('); // Restoring the stack state for backtracking
            }
        }
};