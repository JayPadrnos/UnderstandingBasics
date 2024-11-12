#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
    public:
        vector<vector<int>> subsetsWithDup(vector<int>& nums) {
            vector<vector<int>> result;
            vector<int> subset;
            sort(nums.begin(), nums.end()); // Sort the array to handle duplicates
            generateSubsets(nums, 0, subset, result);
            return result;
        }

    private:
        void generateSubsets(vector<int>& nums, int index, vector<int>& subset, vector<vector<int>>& result) {
            result.push_back(subset); // Add the current subset to the result

            for (int i = index; i < nums.size(); ++i) {
                // Skip duplicates: Ensure we only take the first occurrence of a duplicate in this level of recursion
                if (i > index && nums[i] == nums[i - 1]) {
                    continue;
                }
                subset.push_back(nums[i]); // Include the current element
                generateSubsets(nums, i + 1, subset, result); // Recur with the element
                subset.pop_back(); // Backtrack to explore the other subsets
            }
        }
};