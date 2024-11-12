class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int maxReach = 0;
        
        for (int i = 0; i < n; ++i) {
            if (i > maxReach) {
                return false; // If current index cannot be reached
            }
            maxReach = max(maxReach, i + nums[i]);
            if (maxReach >= n - 1) {
                return true; // If we can reach or exceed the last index
            }
        }
        
        return false;
    }
};
