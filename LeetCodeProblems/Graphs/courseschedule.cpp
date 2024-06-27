class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Step 1: Build the graph
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);

        for (const auto& pair : prerequisites) {
            graph[pair[1]].push_back(pair[0]);
            indegree[pair[0]]++;
        }

        // Step 2: Topological Sort using Kahn's Algorithm (BFS)
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        int count = 0;  // Count of courses that have been processed

        while (!q.empty()) {
            int course = q.front();
            q.pop();
            ++count;

            for (int nextCourse : graph[course]) {
                --indegree[nextCourse];
                if (indegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }

        // If we processed all the courses, return true
        return count == numCourses;
    }
};
