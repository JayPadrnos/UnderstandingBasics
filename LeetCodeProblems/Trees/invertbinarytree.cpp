#include <iostream>
#include <queue>
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
        TreeNode* invertTree(TreeNode* root) {
            if (root == nullptr) // Base case; if root is null return null
            return nullptr;

            // Swap the left and right subtrees
            TreeNode* temp = root->left;
            root->left = invertTree(root->right);
            root->right = invertTree(temp);

            return root;
        }
};

// Function to print the tree level by level (for testing)
void printTree(TreeNode* root) {
    if (root == nullptr)
    return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            cout << node->val << " ";

            if  (node->left != nullptr) 
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
        }
        cout << endl;
    }
}

int main() {
    // Example 1
    TreeNode* root1 = new TreeNode(4);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(7);
    root1->left->left = new TreeNode(1);
    root1->left->right = new TreeNode(3);
    root1->right->left = new TreeNode(6);
    root1->right->right = new TreeNode(9);

    Solution sol;
    TreeNode* invertedRoot1 = sol.invertTree(root1);
    cout << "Inverted Tree 1:" << endl;
    printTree(invertedRoot1);

    return 0;
}