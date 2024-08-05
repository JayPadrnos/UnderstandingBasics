#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        // Sort intervals by their start point
        sort(intervals.begin(), intervals.end());

        // Pair queries with their original indices and sort by query values
        vector<pair<int, int>> sortedQueries;
        for (int i = 0; i < queries.size(); ++i) {
            sortedQueries.push_back({queries[i], i});
        }
        sort(sortedQueries.begin(), sortedQueries.end());

        // Result vector
        vector<int> result(queries.size(), -1);

        // Priority queue to store the intervals (length, end point)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Index to iterate over intervals
        int intervalIndex = 0;

        // Process each query
        for (const auto& [query, originalIndex] : sortedQueries) {
            // Add all intervals that start before or at the current query point to the heap
            while (intervalIndex < intervals.size() && intervals[intervalIndex][0] <= query) {
                int left = intervals[intervalIndex][0];
                int right = intervals[intervalIndex][1];
                int length = right - left + 1;
                pq.push({length, right});
                ++intervalIndex;
            }

            // Remove intervals that end before the current query point
            while (!pq.empty() && pq.top().second < query) {
                pq.pop();
            }

            // The top of the heap is the smallest interval containing the query point
            if (!pq.empty()) {
                result[originalIndex] = pq.top().first;
            }
        }

        return result;
    }
};
