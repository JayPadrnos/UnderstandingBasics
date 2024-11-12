#include <unordered_map>
#include <map>
#include <string>
using namespace std;

class TimeMap {
    private:
        unordered_map<string, map<int, string>> data;
    
    public:
        TimeMap() {
            // Constructor
        }

        void set(string key, string value, int timestamp) {
            // Store the key, value, and timestamp
            data[key][timestamp] = value;
        }

        string get(string key, int timestamp) {
            // Retrieve the value associated with the key at specified timestamp
            if (data.find(key) == data.end())
                return ""; // Key not found

            auto& timeline = data[key];
            auto it = timeline.upper_bound(timestamp);

            if (it == timeline.begin())
                return ""; // No value at or before the given timestamp

            // Return the value associated with the largest timestamp <= given timestamp
            return prev(it)->second;
        }
};