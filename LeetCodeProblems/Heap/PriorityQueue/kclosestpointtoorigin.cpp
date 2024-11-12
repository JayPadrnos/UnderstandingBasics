#include <vector>
#include <queue>
#include <cmath>

using namespace std;

class Solution {
    public:
        vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
            // Define a max heap where the top element is the farthest among the k closest points
            priority_queue<pair<int, vector<int>>> maxHeap;

            for (auto& point : points) {
                int x = point[0];
                int y = point[1];
                int dist = x * x + y * y; // Use squared distance to avoid floating point prescision issues

                // Push the current point and its distance to the heap
                maxHeap.push({dist, point});

                // If the heap size exceeds k, remove the farthest point ( top of the max heap )
                if (maxHeap.size() > k) {
                    maxHeap.pop();
                }
            }

            // Extract the k closest points from the heap
            vector<vector<int>> result;
            while (!maxHeap.empty()) {
                result.push_back(maxHeap.top().second);
                maxHeap.pop();
            }

            return result;
        }
};