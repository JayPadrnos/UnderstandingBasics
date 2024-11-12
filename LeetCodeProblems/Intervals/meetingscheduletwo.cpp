#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Interval {
    public:
        int start, end;
        Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        if (intervals.empty()) return 0;

        // Correct this line to properly sort the intervals
        sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
            return a.start < b.start;
        });

        // Initialize a min-heap to keep track of end times
        priority_queue<int, vector<int>, greater<int>> minHeap;

        // Add the first meeting's end time to the heap
        minHeap.push(intervals[0].end);

        // Iterate over the remaining meetings
        for (size_t i = 1; i < intervals.size(); ++i) {
            // If the current meeting starts after the earliest meeting ends, reuse that room
            if (intervals[i].start >= minHeap.top()) {
                minHeap.pop();
            }
            // Add the current meeting's end time to the heap
            minHeap.push(intervals[i].end);
        }

        // The size of the heap is the minimum number of rooms required
        return minHeap.size();
    }
};
