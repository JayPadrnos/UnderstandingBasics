#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    public:
        bool isSameTree(TreeNode* p, TreeNode* q) {
            // If both trees are empty, they are the same
            if (!p && !q) return true;

            // If one of the trees is empty while the other is not, they are not the same
            if (!p || !q) return false;

            // If the values of the nodes are different, the trees are not the same
            if (p->val != q->val) return false;

            // Recursively check if the left subtree and right subtree are the same
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        }
};