#include <vector>
#include <deque>

using namespace std;

class Solution {
    public: 
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
            vector<int> result;
            deque<int> dq; // deque to store indices

            for (int i = 0; i < nums.size(); ++i) {
                // Remove indices not within the current window
                if (!dq.empty() && dq.front() == i - k)
                    dq.pop_front();

                // Remove elements from deque where corresponding nums value <= current nums[i]
                while (!dq.empty() && nums[dq.back()] <= nums[i])
                    dq.pop_back();

                // Push current index to deque
                dq.push_back(i);

                // Start adding results after first k-1 elements
                if (i >= k - 1)
                    result.push_back(nums[dq.front()]);
            }

            return result;
        }
};
