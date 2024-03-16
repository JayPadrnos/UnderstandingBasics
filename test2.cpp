#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        // Step 1: Create a hash map to store frequency of each element
        std::unordered_map<int, int> freqMap;
        for (int num : nums) {
            freqMap[num]++;
        }
        
        // Step 2: Create a max heap of pairs (frequency, element)
        auto comparator = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.first < b.first; // Compare frequencies
        };
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comparator)> maxHeap(comparator);
        
        for (const auto& entry : freqMap) {
            maxHeap.push({entry.second, entry.first}); // (frequency, element)
            if (maxHeap.size() > k) {
                maxHeap.pop(); // Keep only top k frequent elements
            }
        }
        
        // Step 3: Extract top k frequent elements from the max heap
        std::vector<int> result;
        while (!maxHeap.empty()) {
            result.push_back(maxHeap.top().second); // Extract element
            maxHeap.pop();
        }
        
        return result;
    }
};
//