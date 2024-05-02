#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            // If both p and q are greater than the current node's value, move to the right subtree
            if (p->val > root->val && q->val > root->val) {
                return lowestCommonAncestor(root->right, p, q);
            }
            // If both p and q are smaller than the current node's value, move to the left subtree
            else if (p->val < root->val && q->val < root->val) {
                return lowestCommonAncestor(root->left, p, q);
            }
            // If one node is on the left and the other is on the right,or if one of them is the current node,
            // then the current node is the lowest common ancestor
            else {
                return root;
            }
        }
};