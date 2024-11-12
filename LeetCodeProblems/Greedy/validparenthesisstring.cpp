class Solution {
public:
    bool checkValidString(string s) {
        int minOpen = 0, maxOpen = 0;
        
        for (char c : s) {
            if (c == '(') {
                minOpen++;
                maxOpen++;
            } else if (c == ')') {
                minOpen--;
                maxOpen--;
            } else { // c == '*'
                minOpen--;
                maxOpen++;
            }
            
            // If at any point, the minimum open count goes below 0, reset it to 0
            if (minOpen < 0) minOpen = 0;
            
            // If maxOpen becomes negative, it means we have more ')' than we can balance
            if (maxOpen < 0) return false;
        }
        
        // If minOpen is 0, it means all open parentheses have been matched
        return minOpen == 0;
    }
};
