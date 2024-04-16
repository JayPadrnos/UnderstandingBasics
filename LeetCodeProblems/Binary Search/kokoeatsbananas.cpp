#include <vector>
#include <cmath>
#include <algorithm>

class Solution {
    public:
        int minEatingSpeed(std::vector<int>& piles, int h) {
            int left = 1;
            int right = *std::max_element(piles.begin(), piles.end()); // Maximum pile size

            while (left < right) {
                int mid = left + (right - left) / 2;
                if (canFinish(piles, h, mid)) {
                    right = mid; // Try for a smaller eating speed
                } else {
                    left = mid + 1; // Increase eating speed
                }
            }

            return left;
        }

        private:
            bool canFinish(const std::vector<int>& piles, int h, int k) {
                int hoursRequired = 0;
                for (int pile : piles) {
                    hoursRequired += std::ceil(static_cast<double>(pile) / k);
                }
                return hoursRequired <= h;
            }
};