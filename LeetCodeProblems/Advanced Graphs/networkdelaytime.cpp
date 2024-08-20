#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Step 1: Create an adjacency list
        unordered_map<int, vector<pair<int, int>>> graph;
        for (const auto& time : times) {
            int u = time[0], v = time[1], w = time[2];
            graph[u].emplace_back(v, w);
        }

        // Step 2: Use a priority queue (min-heap) to implement Dijkstra's algorithm
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, k); // (distance, node)
        
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;

        while (!pq.empty()) {
            auto [current_dist, u] = pq.top();
            pq.pop();

            if (current_dist > dist[u]) continue;

            for (auto& [v, w] : graph[u]) {
                if (current_dist + w < dist[v]) {
                    dist[v] = current_dist + w;
                    pq.emplace(dist[v], v);
                }
            }
        }

        // Step 3: Find the maximum time from the starting node k to any other node
        int max_time = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INT_MAX) return -1; // If any node is unreachable
            max_time = max(max_time, dist[i]);
        }

        return max_time;
    }
};
