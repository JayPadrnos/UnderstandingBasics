#include <algorithm> // for std::max
#include <iostream>
#include <stack>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
    public:
        int goodNodes(TreeNode* root) {
            if (root == nullptr) return 0;

            int count = 0;
            std::stack<std::pair<TreeNode*, int>> nodeStack; // Stack to simulate recursion
            nodeStack.push({root, root->val}); // Push the root node onto the stack along with its maximum value encountered so far

            while (!nodeStack.empty()) {
                auto [node, maxValue] = nodeStack.top();
                nodeStack.pop();

                // Check if the current node is good
                if (node->val >= maxValue) {
                    count++;
                }

                // Update the maximum value encountered so far
                maxValue = std::max(maxValue, node->val);

                // Push the child nodes onto the stack with the updated maximum value
                if (node->right != nullptr) {
                    nodeStack.push({node->right, maxValue});
                }
                if (node->left != nullptr) {
                    nodeStack.push({node->left, maxValue});
                }
            }

            return count;
        }
};