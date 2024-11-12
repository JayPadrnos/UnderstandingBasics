#include <vector>
#include <unordered_set>
#include <queue>
#include <string>

#include <iostream>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) { // Check if endWord is in the wordList
            return 0;
        }

        queue<pair<string, int>> q;
        q.push({beginWord, 1});

        while (!q.empty()) {
            string word = q.front().first;
            int length = q.front().second;
            q.pop();

            if (word == endWord) { // Check if the current word is the endWord
                return length;
            }

            for (int i = 0; i < word.size(); i++) { // Corrected loop syntax
                char originalChar = word[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    if (word[i] == c) continue; // Skip if the character is the same
                    word[i] = c;
                    if (wordSet.find(word) != wordSet.end()) { // Check if the transformed word is in the wordSet
                        q.push({word, length + 1});
                        wordSet.erase(word); // Remove the word from the set to avoid revisiting
                    }
                }
                word[i] = originalChar;
            }
        }

        return 0; // Return 0 if no transformation sequence is found
    }
};

int main() {
    Solution sol;
    vector<string> wordList1 = {"bat","bag","sag","dag","dot"};
    cout << sol.ladderLength("cat", "sag", wordList1) << endl; // Output: 4

    vector<string> wordList2 = {"bat","bag","sat","dag","dot"};
    cout << sol.ladderLength("cat", "sag", wordList2) << endl; // Output: 0

    return 0;
}




