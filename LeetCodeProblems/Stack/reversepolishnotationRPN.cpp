#include <vector>
#include <string>
#include <stack>
#include <cstdlib> // for stoi

using namespace std;

class Solution {
    public:
        int evalRPN(vector<string>& tokens) {
            stack<int> st;
            for (const string& token : tokens) {
                if (is_operator(token)) {
                    int operand2 = st.top();
                    st.pop();
                    int operand1 = st.top();
                    st.pop();
                    int result = evaluate(token, operand1, operand2);
                    st.push(result);
                } else {
                    st.push(stoi(token.c_str())); // Convert string to integer
                }
            }
            return st.top();
        }

        private:
            bool is_operator(const string& token) {
                return token == "+" || token == "-" || token == "*" || token == "/";
            }

            int evaluate(const string& op, int operand1, int operand2) {
                if (op == "+") {
                    return operand1 + operand2;
                } else if (op == "-") {
                    return operand1 - operand2;
                } else if (op == "*") {
                    return operand1 * operand2;
                } else {    // Assuming no division by zero as per constraints
                    return operand1 / operand2;
                }
            }
};