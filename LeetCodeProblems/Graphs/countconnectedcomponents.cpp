#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    void dfs(int node, vector<vector<int>>& adjList, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adjList, visited);
            }
        }
    }
    
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adjList(n);
        for (const auto& edge : edges) {
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> visited(n, false);
        int componentCount = 0;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                ++componentCount;
                dfs(i, adjList, visited);
            }
        }
        
        return componentCount;
    }
};
