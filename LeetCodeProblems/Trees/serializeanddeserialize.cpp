#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Def for binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
    public:

        // Encode a tree to a single string.
        string serialize(TreeNode* root) {
            ostringstream out;
            serializeHelper(root, out);
            return out.str();
        }

        // Decode the encoded data to tree
        TreeNode* deserialize(string data) {
            istringstream in(data);
            return deserializeHelper(in);
        }

    private:
        void serializeHelper(TreeNode* root, ostringstream& out) {
            if (root) {
                out << root->val << ' ';
                serializeHelper(root->left, out);
                serializeHelper(root->right, out);
            } else {
                out << "null ";
            }
        }

        TreeNode* deserializeHelper(istringstream& in) {
            string val;
            in >> val;
            if (val == "null") {
                return nullptr;
            }
            TreeNode* root = new TreeNode(stoi(val));
            root->left = deserializeHelper(in);
            root->right = deserializeHelper(in);
            return root;
        }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

// Helper function to print the tree
void printTree(TreeNode* root) {
    if (root == nullptr)
        return;
    cout << root->val << " ";
    printTree(root->left);
    printTree(root->right);
}

int main() {
    Codec codec;
    // Example 1
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->right->left = new TreeNode(4);
    root1->right->right = new TreeNode(5);

    string serialized1 = codec.serialize(root1);
    cout << "Serialized: " << serialized1 << endl;

    TreeNode* deserialized1 = codec.deserialize(serialized1);
    cout << "Deserialized: ";
    printTree(deserialized1);
    cout << endl;

    // Example 2
    TreeNode* root2 = nullptr;
    string serialized2 = codec.serialize(root2);
    cout << "Serialized: " << serialized2 << endl;

    TreeNode* deserialized2 = codec.deserialize(serialized2);
    cout << "Deserialized: ";
    printTree(deserialized2);
    cout << endl;

    return 0;
}