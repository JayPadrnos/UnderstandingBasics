#include <vector>
using namespace std;

class Solution {
    public:
        vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
            vector<vector<int>> result;
            vector<int> currentCombination;
            backtrack(candidates, target, 0, currentCombination, result);
            return result;
        }

    private:
        void backtrack(vector<int>& candidates, int target, int start, vector<int>& currentCombination, vector<vector<int>>& result) {
            // Base case: if the target is 0, we've found a valid combination
            if (target == 0) {
                result.push_back(currentCombination);
                return;
            }

            // Explore each candidate starting from the current index
            for (int i = start; i < candidates.size(); ++i) {
                // If the current candidate exceeds the target, skip it
                if (candidates[i] > target) continue;

                // Include the current candidate in the combination
                currentCombination.push_back(candidates[i]);

                // Recurse with the updated target, allowing the same candidate to be reused
                backtrack(candidates, target - candidates[i], i, currentCombination, result);

                // Backtrack: remove the last included candidate to explore other possibilities
                currentCombination.pop_back();
            }
        }
};