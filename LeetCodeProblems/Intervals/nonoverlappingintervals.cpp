#include <vector>
#include <algorithm>

class Solution {
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
        // Edge case: if there are no intervals or only one interval
        if (intervals.empty()) return 0;
        
        // Sort intervals based on their end times
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[1] < b[1];
        });
        
        int count = 0;
        int end = intervals[0][1];
        
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] < end) {
                // Overlapping interval, increment the count of removals
                ++count;
            } else {
                // Update end to the end of the current interval
                end = intervals[i][1];
            }
        }
        
        return count;
    }
};
