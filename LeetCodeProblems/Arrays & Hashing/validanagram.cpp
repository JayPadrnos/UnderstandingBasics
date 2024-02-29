#include <string>
#include <unordered_map>

class Solution {
public:
    bool isAnagram(std::string s, std::string t) {
        if (s.length() != t.length()) {
            return false; // Anagrams must have the same length
        }

        std::unordered_map<char, int> frequency;

        // Count the frequency of the characters in string s
        for (char c : s) {
            frequency[c]++;
        }

        // Decrement the frequency of characters in string t
        // If a character doesn't exist in s, or its frequency becomes negative, then t is not an anagram
        for (char c : t) {
            frequency[c]--;
            if (frequency[c] < 0) {
                return false;
            }
        }

        return true; // IF all the characters are accounted for, t is an anagram of s
    }
};