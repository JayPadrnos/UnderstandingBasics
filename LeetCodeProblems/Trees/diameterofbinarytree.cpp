#include <iostream>
#include <algorithm>

//  Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    public:
        int diameterOfBinaryTree(TreeNode* root) {
            int maxDiameter = 0;
            maxDepth(root, maxDiameter);
            return maxDiameter;
        }

    private:
        int maxDepth(TreeNode* node, int& maxDiameter) {
            if (node == nullptr) {
                return 0; // Base case: empty tree has depth 0
            } else {
                int leftDepth = maxDepth(node->left, maxDiameter); // Recursively find depth of left subtree
                int rightDepth = maxDepth(node->right, maxDiameter); // Recursively find the depth of the right subtree
                // Update the max diameter encountered so far
                maxDiameter = std::max(maxDiameter, leftDepth + rightDepth);
                // Return the depth of the current node
                return 1 + std::max(leftDepth, rightDepth);
            }
        }
};
 