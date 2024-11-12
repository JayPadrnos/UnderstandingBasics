#include <vector>
#include <stack>

class Solution {
    public:
        std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
            std::vector<int> answer(temperatures.size(), 0);
            std::stack<int> st;

            for (int i = 0; i < temperatures.size(); ++i) {
                while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                    int prevIndex = st.top();
                    st.pop();
                    answer[prevIndex] = i - prevIndex;
                }
                st.push(i);
            }
            return answer;
        }
};