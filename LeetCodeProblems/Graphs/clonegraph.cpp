#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;


/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        unordered_map<Node*, Node*> clones;
        stack<Node*> to_visit;

        clones[node] = new Node(node->val);
        to_visit.push(node);

        while (!to_visit.empty()) {
            Node* current = to_visit.top();
            to_visit.pop();

            for (Node* neighbor : current->neighbors) {
                if (clones.find(neighbor) == clones.end()) {
                    clones[neighbor] = new Node(neighbor->val);
                    to_visit.push(neighbor);
                }
                clones[current]->neighbors.push_back(clones[neighbor]);
            }
        }

        return clones[node];
    }
};