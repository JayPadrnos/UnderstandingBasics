#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;


class Solution {
    public:
        vector<vector<string>> groupAnagrams(vector<string>& strs) {
            unordered_map<string, vector<string>> anagramGroups;

            // Iterate through each string in the input array
            for (const string& str : strs) {
                // Sort the characters of the string to get a unique representation
                string sortedStr = str;
                sort(sortedStr.begin(), sortedStr.end());

                // Add the string to the corresponding group in the hash map
                anagramGroups[sortedStr].push_back(str);
            }

            // Prepare the output vector
            vector<vector<string>> result;

            // Iterate through the has map and add the gorups to the output vector
            for (const auto& pair : anagramGroups) {
                result.push_back(pair.second);
            }

            return result;
        }
};



// This solution has a time complexity of O(n*m*log(m)), where n is the number of strings in the input array and m is the max length of a string
// due to the has map the overall space complexity is O(n*m) due to the hash map