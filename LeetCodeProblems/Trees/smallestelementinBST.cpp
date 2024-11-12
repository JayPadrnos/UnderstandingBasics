#include <iostream>
#include <stack>

using namespace std;

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
        int kthSmallest(TreeNode* root, int k) {
            stack<TreeNode*> s;
            TreeNode* curr = root;
            int count = 0;

            while (curr != nullptr || !s.empty()) {
                while (curr != nullptr) {
                    s.push(curr);
                    curr = curr->left;
                }

                curr = s.top();
                s.pop();
                count++;

                if (count == k)
                    return curr->val;

                curr = curr->right;
            }

            return -1; // Invalid input or k out of range
        }
};