#include <vector>

class Solution {
public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges) {
        int n = edges.size();
        // Initialize Union-Find structure
        std::vector<int> parent(n + 1);
        std::vector<int> rank(n + 1, 0);
        
        // Initially, each node is its own parent
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
        
        // Process each edge
        for (const auto& edge : edges) {
            if (!unionNodes(edge[0], edge[1], parent, rank)) {
                return edge;
            }
        }
        
        return {}; // If no redundant edge found (though problem guarantees there is one)
    }
    
private:
    // Function to find the root of a node with path compression
    int find(int x, std::vector<int>& parent) {
        if (parent[x] != x) {
            parent[x] = find(parent[x], parent);
        }
        return parent[x];
    }
    
    // Function to union two nodes with union by rank
    bool unionNodes(int x, int y, std::vector<int>& parent, std::vector<int>& rank) {
        int rootX = find(x, parent);
        int rootY = find(y, parent);
        
        if (rootX == rootY) {
            return false; // They are already in the same component
        }
        
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};
