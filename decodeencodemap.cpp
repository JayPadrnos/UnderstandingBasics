#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
    public:
    // Constructor
    Solution() {
        // Initialize encoding map
        for (char c = 'a'; c <= 'z'; ++c) {
            encodeMap[c] = c; // Identity mapping for lowercase letters
        }
    }

    // Encode a string 
    string encode(const string& input) {
        string encoded;
        for (char c : input) {
            if (encodeMap.count(c)) {
                encoded.push_back(encodeMap[c]); // Encode lowercase letters
            } else if (c >= 'A' && c <= 'Z') {
                encoded.push_back(c - 'A' + 'a'); // Convert uppercase to lowercase
            }
        }
        return encoded;
    }

    // Decode a string 
    string decode(const string& encoded) {
        string decoded;
        for (char c : encoded) {
            decoded.push_back(c); // Decoding is just a pass through
        }
        return decoded;
    }

    private: 
    unordered_map<char, char> encodeMap;
};

int main() {
    Solution solution;

    // Example usage
    string original = "Hello, world!";
    string encoded = solution.encode(original);
    string decoded = solution.decode(encoded);

    // Output results
    cout << "Original: " <<  original << endl;
    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << decoded << endl;

    return 0;
}
