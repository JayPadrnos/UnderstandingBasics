#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        if (nums.size() == 2) return max(nums[0], nums[1]);

        // Helper function to solve the linear house robber problem
        auto robLinear = [](vector<int>& nums) {
            int prev1 = 0, prev2 = 0;
            for (int num : nums) {
                int temp = max(prev1, prev2 + num);
                prev2 = prev1;
                prev1 = temp;
            }
            return prev1;
        };

        // Scenario 1: Exclude the first house
        vector<int> excludeFirst(nums.begin() + 1, nums.end());
        int rob1 = robLinear(excludeFirst);

        // Scenario 2: Exclude the last house
        vector<int> excludeLast(nums.begin(), nums.end() - 1);
        int rob2 = robLinear(excludeLast);

        // Return the maximum of the two scenarios
        return max(rob1, rob2);
    }
};
