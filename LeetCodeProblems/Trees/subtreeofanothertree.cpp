#include <iostream>
#include <queue>
using namespace std;

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
        bool isIdentical(TreeNode* s, TreeNode* t) {
            if (s == nullptr && t == nullptr)
                return true;
            if (s == nullptr || t == nullptr)
                return false;
            return (s->val == t->val) && isIdentical(s->left, t->left) && isIdentical(s->right, t->right);
        }

        bool isSubtree(TreeNode* root, TreeNode* subRoot) {
            if (root == nullptr)
                return false;
            if (isIdentical(root, subRoot))
                return true;
            return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
        }
};