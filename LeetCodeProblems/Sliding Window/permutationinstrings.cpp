#include <string>
#include <vector>

using namespace std;

class Solution {
    public:
        bool checkInclusion(string s1, string s2) {
            // Lengths of strings s1 and s2
            int n = s1.size();
            int m = s2.size();

            if (n > m) {
                return false; // if s1 is longer than s2 no permutation can be a substring
            }

            // Frequency arrays to count characters in s1 and the current window of s2
            vector<int> count1(26, 0); // count characters in s1
            vector<int> count2(26, 0); // count characters in the sliding window

            // fill count1 with character frequencies from s1
            for (char c : s1) {
                count1[c - 'a']++;
            }

            // Initialize the sliding window (first window of size n in s2)
            for (int i = 0; i < n; i++) {
                count2[s2[i] - 'a']++;
            }

            // Compare initial window of s2 with s1
            if (count1 == count2) {
                return true;
            }

            // Slide the window across s2
            for (int i = n; i < m; i++) {
                // Add the new character at the end of the window
                count2[s2[i] - 'a']++;

                // Remove the character that is no longer in the window
                count2[s2[i - n] - 'a']--;

                // Check if the frequency arrays match
                if (count1 == count2) {
                    return true;
                }
            }
            
            return false; // No matching permutation found
        }
};