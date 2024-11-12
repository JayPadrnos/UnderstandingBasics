#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    public:
        vector<vector<int>> permute(vector<int>& nums) {
            vector<vector<int>> result;
            backtrack(nums, result, 0);
            return result;
        }
    
    private:
        void backtrack(vector<int>& nums, vector<vector<int>>& result, int start) {
            if (start == nums.size()) {
                result.push_back(nums);
                return;
            }

            for (int = start; i < nums.size(); ++i) {
                swap(nums[start], nums[i]);
                backtrack(nums, result, start + 1);
                swap(nums[start], nums[i]);
            }
        }
};