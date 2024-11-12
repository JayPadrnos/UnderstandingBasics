#include <vector>
#include <algorithm>
#include <string>

class Solution {
    public:
        int characterReplacement(std::string s, int k) {
            int n = s.size();
            std::vector<int> count(26, 0);  // Count of each character 'A' to 'Z'
            int maxCount = 0;   // Max frequency of any single character in the current window
            int start = 0;  // Start of the current window
            int maxLength = 0;  // Max length of valid substring found

            for (int end = 0; end < n; ++end) {
                maxCount = std::max(maxCount, ++count[s[end] - 'A']);

                // If the window size exceeds the number of charges allowed (k + 1 to include one more change), shrink the window
                while (end - start + 1 - maxCount > k) {
                    --count[s[start] - 'A'];
                    ++start;
                }

                // Update the max length
                maxLength = std::max(maxLength, end - start + 1);
            }

            return maxLength;
        }
};