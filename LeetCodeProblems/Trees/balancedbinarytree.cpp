#include <iostream>
#include <algorithm>


 // Definition for a binary tree node.
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
        bool isBalanced(TreeNode* root) {
            return checkHeight(root) != -1;
        }

    private:
        int checkHeight(TreeNode* node) {
            if (node == nullptr) {
                return 0; // Base case: empty tree has height 0
            } else {
                int leftHeight = checkHeight(node->left); // Height of left subtree
                int rightHeight = checkHeight(node->right); // Height of right subtree

                // If either subtree is unbalanced, or the current node is unbalanced,
                // return -1 to indicate that the tree rooted at this node is unbalanced
                if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) {
                    return -1;
                }

                // Otherwise, return the height of the tree rooted at this node
                return 1 + std::max(leftHeight, rightHeight);
            }
        }
};