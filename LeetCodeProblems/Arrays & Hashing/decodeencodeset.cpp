#include <unordered_set>
#include <string>
#include <iostream>

using namespace std;

class Solution {
    public:
    // Constructor
    Solution() {
        // Initialize encoding set
        for (char c = 'a'; c <= 'z'; ++c) {
            encodeSet.insert(c);
        }
    }

    // Encode a string
    string encode(const string& input) {
        string encoded;
        for (char c : input) {
            if (encodeSet.count(c)) {
                encoded.push_back(c); // Encode lowercase letters
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
            decoded.push_back(c); // Decoding is just a pass-through
        }
        return decoded;
    }

    private:
        unordered_set<char> encodeSet;
};

int main() {
    Solution solution;

    // Example usage
    string original = "Hello, world:";
    string encoded = solution.encode(original);
    string decoded = solution.decode(encoded);

    // Output results
    cout << "Original: " << original << endl;
    cout << "encoded: " << encoded << endl;
    cout << "decoded: " << decoded << endl;

    return 0;
}