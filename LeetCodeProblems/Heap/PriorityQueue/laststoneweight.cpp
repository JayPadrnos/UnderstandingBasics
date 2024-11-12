#include <vector>
#include <queue>

using namespace std;

class Solution {
    public:
        int lastStoneWeight(vector<int>& stones) {
            // Using priority_queue as a max-heap
            priority_queue<int> maxHeap(stones.begin(), stones.end());

            // Continue until there is one or no stones left
            while (maxHeap.size() > 1) {
                // Get the two heaviest stones
                int stone1 = maxHeap.top();
                maxHeap.pop();
                int stone2 = maxHeap.top();
                maxHeap.pop();

                // If they are not equal, push the difference back into the heap
                if (stone1 != stone2) {
                    maxHeap.push(stone1 - stone2);
                }
            }

            // If theres a stone left, return its weight, otherwise return 0
            return maxHeap.empty() ? 0 : maxHeap.top();
        }
};