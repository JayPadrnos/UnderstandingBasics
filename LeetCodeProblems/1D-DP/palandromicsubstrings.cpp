class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length();
        int count = 0;
        
        for (int i = 0; i < n; ++i) {
            // Count odd length palindromes (single character center)
            count += expandAroundCenter(s, i, i);
            // Count even length palindromes (two consecutive characters center)
            count += expandAroundCenter(s, i, i + 1);
        }
        
        return count;
    }
    
private:
    int expandAroundCenter(const string& s, int left, int right) {
        int count = 0;
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            ++count;
            --left;
            ++right;
        }
        return count;
    }
};
