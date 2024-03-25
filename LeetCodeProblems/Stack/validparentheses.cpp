#include <stack>
#include <string>

class Solution {
public:
    bool isValid(std::string s) {
        std::stack<char> st;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                // Push opening brackets onto the stack
                st.push(c);
            } else {
                if (st.empty()) return false; // More closing brackets than opening brackets
                if ((c == ')' && st.top() != '(') ||
                    (c == ']' && st.top() != '[') ||
                    (c == '}' && st.top() != '{')) {
                    // Closing bracket doesn't match the top of the stack
                    return false;
                }
                st.pop(); // Pop the corresponding opening bracket
            }
        }
        return st.empty(); // True if all opening brackets are matched
    }
};