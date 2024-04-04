#include <vector>
#include <algorithm>

class Solution {
    public:
        int maxArea(std::vector<int>& height) {
            int maxArea = 0;
            int left = 0;
            int right = height.size() - 1;

            while (left < right) {
                int minHeight = std::min(height[left], height[right]);
                int width = right - left;
                int area = minHeight * width;
                maxArea = std::max(maxArea, area);

                // Move the pointer pointing to the smaller height
                if (height[left] < height[right]) {
                    left++;
                } else {
                    right--;
                }
            }

            return maxArea;
        }
};