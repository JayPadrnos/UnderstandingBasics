#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> numMap; // Map to store numbers and their indicies

        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];

            // If complement exists in the map, return the indices
            if (numMap.find(complement) != numMap.end()) {
                return { numMap[complement], i };
            }

            // Otherwise store the current number and its index in the map
            numMap[nums[i]] = i;
        }

        // If no solution is found
        return {};
    }
};