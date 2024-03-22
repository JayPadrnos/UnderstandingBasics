#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    int longestConsecutive(std::vector<int>& nums) {
        std::unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLength = 0;

        for (int num : nums) {
            if (numSet.find(num - 1) == numSet.end()) {
            int currNum = num;
            int currLength = 1;

            while (numSet.find(currNum + 1) != numSet.end()); {
                currNum++;
                currLength++;
            }

            maxLength = std::max(maxLength, currLength);
        }
    }

    return maxLength;
    }
};