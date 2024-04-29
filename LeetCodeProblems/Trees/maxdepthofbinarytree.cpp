#include <algorithm> // for std::max


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
        int maxDepth(TreeNode* root) {
            if (root == nullptr) {
                return 0; // Base case: empty tree has depth 0
            } else {
                int leftDepth = maxDepth(root->left);  // Recursively find depth of the left subtree
                int rightDepth = maxDepth(root->right);  // Recursively find depth of right subtree
                return 1 + std::max(leftDepth, rightDepth); // Depth of current node is 1 + max depth of its subtrees
            }
        }
};