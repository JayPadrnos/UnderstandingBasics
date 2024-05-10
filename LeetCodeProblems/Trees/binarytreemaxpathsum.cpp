#include <algorithm> // for max function
#include <climits> // For the INT_MIN const

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    public:
        int maxPathSum(TreeNode* root) {
            int maxSum = INT_MIN; // Initialize maxSum to the min integer value
            maxPathSumHelper(root, maxSum);
            return maxSum;
        }

    private:
        int maxPathSumHelper(TreeNode* node, int& maxSum) {
            if (!node) return 0;

            // Calculate the max sum of left and right subtrees
            int leftMax = std::max(0, maxPathSumHelper(node->left, maxSum));
            int rightMax = std::max(0, maxPathSumHelper(node->right, maxSum));

            // Update maxSum if the current path sum (node + left subtree + right subtree) is greater
            maxSum = std::max(maxSum, node->val + leftMax + rightMax);

            // Return the max sum achievable starting from the current node
            return node->val + std::max(leftMax, rightMax);
        }
};