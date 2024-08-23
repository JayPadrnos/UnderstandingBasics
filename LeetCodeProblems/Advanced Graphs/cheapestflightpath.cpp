#include <vector>
#include <queue>
#include <unordered_map>
#include <limits.h>

using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Create an adjacency list for the graph
        unordered_map<int, vector<pair<int, int>>> graph;
        for (const auto& flight : flights) {
            int from = flight[0], to = flight[1], price = flight[2];
            graph[from].push_back({to, price});
        }
        
        // Priority queue to keep track of the minimum cost to reach each node
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        // (cost, node, stops)
        pq.push({0, src, 0});
        
        // Keep track of the minimum price to reach each node with a certain number of stops
        vector<vector<int>> visited(n, vector<int>(k + 2, INT_MAX));
        visited[src][0] = 0;
        
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            int curCost = cur[0], curNode = cur[1], curStops = cur[2];
            
            // If we reach the destination with valid stops, return the cost
            if (curNode == dst) {
                return curCost;
            }
            
            // If we have exceeded the maximum allowed stops, continue
            if (curStops > k) {
                continue;
            }
            
            // Explore neighboring nodes
            for (const auto& [nextNode, price] : graph[curNode]) {
                int newCost = curCost + price;
                int nextStops = curStops + 1;
                
                // If this path offers a cheaper cost or fewer stops, explore it
                if (newCost < visited[nextNode][nextStops]) {
                    visited[nextNode][nextStops] = newCost;
                    pq.push({newCost, nextNode, nextStops});
                }
            }
        }
        
        return -1; // If no valid path is found
    }
};
