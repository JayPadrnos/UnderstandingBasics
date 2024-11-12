#include <iostream>
#include <string>
#include <vector>
#include <utility>


using namespace std;

class TrieNode {
public:
    vector<TrieNode*> children;
    string word;
    
    TrieNode(): children(26), word("") {}
};

class Trie {
public:
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c - 'a'])
                node->children[c - 'a'] = new TrieNode();
            node = node->children[c - 'a'];
        }
        node->word = word;
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie trie;
        for (string word : words)
            trie.insert(word);
        
        vector<string> result;
        int m = board.size();
        int n = board[0].size();
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                dfs(board, i, j, trie.root, result);
            }
        }
        
        return result;
    }
    
    void dfs(vector<vector<char>>& board, int i, int j, TrieNode* node, vector<string>& result) {
        char c = board[i][j];
        if (c == '#' || !node->children[c - 'a']) return;
        
        node = node->children[c - 'a'];
        if (!node->word.empty()) {
            result.push_back(node->word);
            node->word = "";
        }
        
        board[i][j] = '#';
        
        static vector<pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto& dir : directions) {
            int x = i + dir.first;
            int y = j + dir.second;
            if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size())
                dfs(board, x, y, node, result);
        }
        
        board[i][j] = c;
    }
};