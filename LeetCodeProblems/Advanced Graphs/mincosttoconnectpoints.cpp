#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<bool> inMST(n, false);  // Track nodes already in MST
        vector<int> minDist(n, INT_MAX);  // Min distance to MST
        
        int totalCost = 0;
        int edgesUsed = 0;
        minDist[0] = 0;  // Start from the first point
        
        while (edgesUsed < n) {
            int minCost = INT_MAX;
            int currPoint = -1;
            
            // Find the point not in MST with the smallest distance
            for (int i = 0; i < n; i++) {
                if (!inMST[i] && minDist[i] < minCost) {
                    minCost = minDist[i];
                    currPoint = i;
                }
            }
            
            // Add the chosen point to the MST
            totalCost += minCost;
            inMST[currPoint] = true;
            edgesUsed++;
            
            // Update the minimum distances to the rest of the points
            for (int i = 0; i < n; i++) {
                if (!inMST[i]) {
                    int dist = abs(points[currPoint][0] - points[i][0]) + abs(points[currPoint][1] - points[i][1]);
                    if (dist < minDist[i]) {
                        minDist[i] = dist;
                    }
                }
            }
        }
        
        return totalCost;
    }
};
