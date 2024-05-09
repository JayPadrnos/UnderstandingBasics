#include <vector>
#include <unordered_map>

using namespace std;

// Definition for the binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;    
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    public:
        TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
            // Create a map to store the indicies of elements in the inorder array
            unordered_map<int, int> indexMap;
            for (int i = 0; i <inorder.size(); ++i) {
                indexMap[inorder[i]] = i;
            }

            // Call the recursive helper function
            return buildTreeHelper(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, indexMap);
        }

    private:
        TreeNode* buildTreeHelper(vector<int>& preorder, int preStart, int preEnd,
                                  vector<int>& inorder, int inStart, int inEnd,
                                  unordered_map<int, int>& indexMap) {
        // Base case: if the start index is greater than the end index, return nullptr
        if (preStart > preEnd || inStart > inEnd) {
            return nullptr;
        }

        // The root of the current subtree is the first element of the preorder array
        int rootVal = preorder[preStart];
        TreeNode* root = new TreeNode(rootVal);

        // Find the index of the root in the inorder array
        int rootIndexInInorder = indexMap[rootVal];

        // Calculate the number of elements in the left subtree
        int leftSubtreeSize = rootIndexInInorder - inStart;

        // Recursively build left and right subtree
        root->left = buildTreeHelper(preorder, preStart + 1, preStart + leftSubtreeSize,
                                     inorder, inStart, rootIndexInInorder - 1, indexMap);
        root->right = buildTreeHelper(preorder, preStart + leftSubtreeSize + 1, preEnd,
                                      inorder, rootIndexInInorder + 1, inEnd, indexMap);


                    return root;
                                  }
};

