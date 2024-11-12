#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // Graph represented as an adjacency list with a min-heap for each airport
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> graph;
        
        // Build the graph
        for (auto& ticket : tickets) {
            graph[ticket[0]].push(ticket[1]);
        }
        
        vector<string> itinerary;
        dfs("JFK", graph, itinerary);
        
        // The itinerary is constructed in reverse order, so reverse it
        reverse(itinerary.begin(), itinerary.end());
        return itinerary;
    }
    
private:
    void dfs(const string& airport, unordered_map<string, priority_queue<string, vector<string>, greater<string>>>& graph, vector<string>& itinerary) {
        auto& destinations = graph[airport];
        
        while (!destinations.empty()) {
            // Get the smallest lexical order destination
            string next_destination = destinations.top();
            destinations.pop();
            dfs(next_destination, graph, itinerary);
        }
        
        // Add the airport to the itinerary
        itinerary.push_back(airport);
    }
};
