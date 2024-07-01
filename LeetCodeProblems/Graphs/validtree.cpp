#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) return false; // A tree should have exactly n-1 edges
        
        unordered_map<int, vector<int>> graph;
        for (auto edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        unordered_set<int> visited;
        if (!dfs(0, -1, graph, visited)) return false;
        
        return visited.size() == n; // Check if all nodes are connected
    }

private:
    bool dfs(int node, int parent, unordered_map<int, vector<int>>& graph, unordered_set<int>& visited) {
        if (visited.find(node) != visited.end()) return false;
        
        visited.insert(node);
        
        for (int neighbor : graph[node]) {
            if (neighbor == parent) continue; // Skip the parent node
            if (!dfs(neighbor, node, graph, visited)) return false;
        }
        
        return true;
    }
};
