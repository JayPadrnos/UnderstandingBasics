#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    public:
        int carFleet(int target, vector<int>& position, vector<int>& speed) {
            int n = position.size();
            if (n == 0) return 0;

            // Combine position and speed into pairs and sort based on position
            vector<pair<int, double>> cars;
            for (int i = 0; i < n; ++i) {
                cars.push_back({position[i], static_cast<double>(target - position[i]) / speed[i]});
            }
            sort(cars.begin(), cars.end());

            int fleets = 1;
            double current_time = cars[n - 1].second; // last car
            for (int i = n - 2; i >= 0; --i) {
                if (cars[i].second > current_time) {
                    // if the current car arrives later than the previous one, it forms a new fleet
                    fleets++;
                    current_time = cars[i].second;
                }
            }

            return fleets;
        }
};