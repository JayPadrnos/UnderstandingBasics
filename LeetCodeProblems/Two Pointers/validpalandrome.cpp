#include <string>
#include <cctype>

using namespace std;

class Solution {
    public:
        bool isPalindrome(string s) {
            // Step 1 convert uppercase to lowercase letters
            for (char& c : s) {
                c = tolower(c);
            }

            // Step 2 remove non alphanumeric characters
            string cleanString;
            for (char c : s) {
                if (isalnum(c)) {
                    cleanString += c;
                }
            }

            // Step 3 Check if it's a palindrome
            int left = 0;
            int right = cleanString.length() - 1;
            while (left < right) {
                if (cleanString[left] != cleanString[right]) {
                    return false;
                }
                left++;
                right--;
            }
            return true;
        }
};