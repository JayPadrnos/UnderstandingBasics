#include <vector>
#include <queue>

using namespace std;

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
        vector<int> rightSideView(TreeNode* root) {
            vector<int> result;
            if (!root)
                return result;

            queue<TreeNode*> levelQueue;
            levelQueue.push(root);

            while (!levelQueue.empty()) {
                int size = levelQueue.size();
                for (int i = 0; i < size; ++i) {
                    TreeNode* node = levelQueue.front();
                    levelQueue.pop();
                    // If it's the last node at this level, add it to the result
                    if (i == size - 1)
                        result.push_back(node->val);
                    // Add the children to the queue for the next level
                    if (node->left)
                        levelQueue.push(node->left);
                    if (node->right)
                        levelQueue.push(node->right);
                }
            }

            return result;
        }
};