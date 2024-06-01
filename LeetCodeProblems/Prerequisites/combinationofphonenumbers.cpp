#include <vector>
#include <string>
using namespace std;

class Solution {
    public:
        vector<string> letterCombinations(string digits) {
            if (digits.empty()) {
                return {};
            }

            // Mapping of digits to correspond letters
            vector<string> digitToChar = {
                "",
                "",
                "abc",
                "def",
                "ghi",
                "jkl",
                "mno",
                "pqrs",
                "tuv",
                "wxyz"
            };

            vector<string> result;
            string currentCombination;

            // Start the backtracking process
            backtrack(digits, 0, currentCombination, result, digitToChar);

            return result;
        }

    private:
        void backtrack(const string& digits, int index, string& currentCombination, vector<string>& result, const vector<string>& digitToChar) {
            // Base case: if the current combination is the same length as digits, we've found a valid combination
            if (index == digits.length()) {
                result.push_back(currentCombination);
                return;
            }

            // Get the corresponding letters for the current digit
            string letters = digitToChar[digits[index] - '0'];

            for (char letter : letters) {
                // Add the letter to the current combination
                currentCombination.push_back(letter);
                // Move on the next digit
                backtrack(digits, index + 1, currentCombination, result, digitToChar);
                // Backtrack: remove the letter before moving on to the next
                currentCombination.pop_back();
            }
        }
};