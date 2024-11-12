#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};

        // Step 1: Sort the intervals based on the start time
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> merged;
        merged.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); ++i) {
            // Get the last interval in merged
            vector<int>& last = merged.back();
            // Check if the current interval overlaps with the last merged interval
            if (intervals[i][0] <= last[1]) {
                // Merge the intervals
                last[1] = max(last[1], intervals[i][1]);
            } else {
                // No overlap, add the current interval to merged
                merged.push_back(intervals[i]);
            }
        }

        return merged;
    }
};
