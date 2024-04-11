#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
using namespace std;

class Solution {
    public:
        string minWindow(string s, string t) {
            vector<int> targetFreq(128, 0); // frequency arra for the string t
            vector<int> windowFreq(128, 0); // frequency array for the current window in s

            // Calculate frequency of characters in t
            for (char c : t) {
                targetFreq[c]++;
            }

            int left = 0, right = 0;
            int minLeft = 0, minRight = 0;
            int minLength = numeric_limits<int>::max();
            int requiredChars = t.length(); // number of characters to be found

            while (right < s.length()) {
                char currentChar = s[right];
                windowFreq[currentChar]++;
                if (windowFreq[currentChar] <= targetFreq[currentChar]) {
                    requiredChars--;
                }

                // Try to shrink the window from the left
                while (requiredChars == 0) {
                    // Update the minimum window found
                    if (right - left + 1 < minLength) {
                        minLength = right - left + 1;
                        minLeft = left;
                        minRight = right;
                    }

                    char leftChar = s[left];
                    windowFreq[leftChar]--;
                    if (windowFreq[leftChar] < targetFreq[leftChar]) {
                        requiredChars++;
                    }
                    left++;
                }

                right++;
            }

            // If minLength is still the max no valid window found
            if (minLength == numeric_limits<int>::max()) {
                return "";
            }

            return s.substr(minLeft, minLength);
        }
};