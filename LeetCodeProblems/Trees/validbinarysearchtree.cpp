#include <climits> // for INT_MIN and INT_MAX

class Solution {
    public:
        bool isValidBST(TreeNode* root) {
            return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
        }

    private:
        bool isValidBSTHelper(TreeNode* root, long minVal, long maxVal) {
            if (root == nullptr)
                return true;

            // Check if the current node's value is within the valid range
            if (root->val <= minVal || root->val >= maxVal)
                return false;

            // Check the left subtree with updated max value as current node's value
            // and right subtree with updated min value as current node's value
            return isValidBSTHelper(root->left, minVal, root->val) &&
                   isValidBSTHelper(root->right, root->val, maxVal);
        }
};