#include <unordered_map>
#include <vector>
using namespace std;

class CountSquares {
private:
    unordered_map<int, unordered_map<int, int>> points; // store frequency of each point

public:
    CountSquares() {
        points.clear();
    }
    
    // Adds a new point [x, y]
    void add(vector<int> point) {
        points[point[0]][point[1]]++; // increment the count of point [x, y]
    }
    
    // Counts the number of squares that can be formed with [x, y]
    int count(vector<int> point) {
        int x = point[0], y = point[1];
        int totalSquares = 0;

        // Iterate over all points with the same x-coordinate as the query point
        for (auto& [ny, freq] : points[x]) {
            int side = abs(ny - y);
            if (side == 0) continue; // skip the point itself

            // Check for the four points that can form a square
            // Points are (x, ny), (x + side, y), (x + side, ny)
            if (points[x + side][y] > 0 && points[x + side][ny] > 0) {
                totalSquares += points[x][ny] * points[x + side][y] * points[x + side][ny];
            }

            // Points are (x, ny), (x - side, y), (x - side, ny)
            if (points[x - side][y] > 0 && points[x - side][ny] > 0) {
                totalSquares += points[x][ny] * points[x - side][y] * points[x - side][ny];
            }
        }

        return totalSquares;
    }
};
