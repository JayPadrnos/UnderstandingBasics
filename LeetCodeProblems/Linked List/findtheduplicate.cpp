#include <vector>

class Solution {
    public:
        int findDuplicate(const std::vector<int>& nums) {
            // Use the concept of fast and slow pointers to detect the cycle
            int slow = nums[0];
            int fast = nums[0];

            // Phase 1: Find the intersection point of the two pointers
            do {
                slow = nums[slow];  // Move one step
                fast = nums[nums[fast]]; // Move to steps
            } while (slow != fast);

            // Phase 2: Find the entrance to the cycle
            // Reset one pointer to the start and move both pointers at the same speed
            int entry = nums[0];
            while (entry != slow) {
                entry = nums[entry];
                slow = nums[slow];
            }

            // When they meet again, it's at the enterance to the cycle
            return entry;
        }
};