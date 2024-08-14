#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
    std::vector<int> partitionLabels(std::string s) {
        // Step 1: Record the last occurrence of each character
        std::unordered_map<char, int> last_occurrence;
        for (int i = 0; i < s.length(); ++i) {
            last_occurrence[s[i]] = i;
        }
        
        // Step 2: Partition the string
        std::vector<int> partitions;
        int start = 0, end = 0;
        for (int i = 0; i < s.length(); ++i) {
            end = std::max(end, last_occurrence[s[i]]);
            if (i == end) {
                partitions.push_back(end - start + 1);
                start = i + 1;
            }
        }
        
        return partitions;
    }
};
