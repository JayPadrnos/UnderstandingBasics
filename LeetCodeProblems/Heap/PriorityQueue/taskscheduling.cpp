#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    public:
        int leastInterval(vector<char>& tasks, int n) {
            // Step 1: Count the frequency of each task
            vector<int> freq(26, 0);
            for (char task : tasks) {
                freq[task - 'A']++;
            }

            // Step 2: Sort the frequencies in descending order
            sort(freq.begin(), freq.end(), greater<int>());

            // Step 3: Find the task with the highest frequency
            int maxFreq = freq[0];
            int idleTime = (maxFreq - 1) * n;

            // Step 4: Subtract the frequency of the other tasks from the idle time
            for (int i = 1; i < 26 && idleTime > 0; i++) {
                idleTime -= min(freq[i], maxFreq - 1);
            }

            // Step 5: If idleTime is negative, it means we don't need any idle slots
            idleTime = max(0, idleTime);

            // Step 6: Return the total time, which is the sum of tasks and idleTime
            return tasks.size() + idleTime;
        }
}