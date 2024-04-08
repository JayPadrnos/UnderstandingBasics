#include <string>
#include <unordered_map>
#include <algorithm>

class Solution {
    public:
        int lengthOfLongestSubstring(std::string s) {
            std::unordered_map<char, int> charMap;
            int maxLength = 0;
            int start = 0;

            for (int end = 0; end < s.length(); ++end) {
                char currentChar = s[end];

                if (charMap.find(currentChar) != charMap.end() && charMap[currentChar] >= start) {
                    start = charMap[currentChar] + 1;
                }

                charMap[currentChar] = end;
                maxLength = std::max(maxLength, end - start + 1);
            }

            return maxLength;
        }
};