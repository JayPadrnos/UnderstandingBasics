#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class Solution {
public:
    string foreignDictionary(vector<string>& words) {
        // Step 1: Build the graph
        unordered_map<char, unordered_set<char>> adjList;
        unordered_map<char, int> inDegree;
        
        // Initialize in-degree for all characters
        for (const auto& word : words) {
            for (char c : word) {
                inDegree[c] = 0;
            }
        }

        // Compare adjacent words to build the graph
        for (int i = 0; i < words.size() - 1; ++i) {
            string word1 = words[i];
            string word2 = words[i + 1];
            int minLength = min(word1.length(), word2.length());
            bool foundOrder = false;
            
            for (int j = 0; j < minLength; ++j) {
                char c1 = word1[j];
                char c2 = word2[j];
                if (c1 != c2) {
                    if (!adjList[c1].count(c2)) {
                        adjList[c1].insert(c2);
                        inDegree[c2]++;
                    }
                    foundOrder = true;
                    break;
                }
            }
            
            // If no order was found and word1 is longer than word2, the order is invalid
            if (!foundOrder && word1.length() > word2.length()) {
                return "";
            }
        }
        
        // Step 2: Topological Sort using BFS (Kahn's algorithm)
        queue<char> q;
        string result;

        // Start with nodes that have zero in-degree
        for (const auto& pair : inDegree) {
            if (pair.second == 0) {
                q.push(pair.first);
            }
        }

        while (!q.empty()) {
            char curr = q.front();
            q.pop();
            result += curr;

            // Decrease the in-degree of neighboring nodes
            for (char neighbor : adjList[curr]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // If the result length doesn't match the number of unique characters, there was a cycle
        if (result.length() != inDegree.size()) {
            return "";
        }

        return result;
    }
};
