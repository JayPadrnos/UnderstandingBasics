#include <iostream>
#include <unordered_map>
using namespace std;

class TrieNode {
    public:
        unordered_map<char, TrieNode*> children;
        bool isEnd;

        TrieNode() {
            isEnd = false;
        }
};

class WordDictionary {
    private:
        TrieNode* root;

        bool searchUntil(TrieNode* node, string word, int index) {
            if (index == word.length()) {
                return node->isEnd;
            }

            char ch = word[index];
            if (ch == '.') {
                for (auto it = node->children.begin(); it != node->children.end(); ++it) {
                    if (searchUntil(it->second, word, index + 1)) {
                        return true;
                    }
                }
                return false;
            } else {
                if (node->children.find(ch) != node->children.end()) {
                    return searchUntil(node->children[ch], word, index + 1);
                } else {
                    return false;
                }
            }
        }

    public:
        WordDictionary() {
            root = new TrieNode();
        }

        void addWord(string word) {
            TrieNode* node = root;
            for (char ch : word) {
                if (node->children.find(ch) == node->children.end()) {
                    node->children[ch] = new TrieNode();
                }
                node = node->children[ch];
            }
            node->isEnd = true;
        }

        bool search(string word) {
            return searchUntil(root, word, 0);
        }
};

int main() {
    WordDictionary wordDictionary;

    wordDictionary.addWord("bad");

    cout << wordDictionary.search("bad") << endl;
}