#include <unordered_map>

class Node {
    public:
        int val;
        Node* next;
        Node* random;

        Node(int _val) {
            val = _val;
            next = NULL;
            random = NULL;
        }
};

class Solution {
    public:
        Node* copyRandomList(Node* head) {
            if (head == nullptr) return nullptr;

            // Map to store original nodes and their corresponding copied nodes
            std::unordered_map<Node*, Node*> nodeMap;

            // Creat a dummy node for the new list's head
            Node* dummy = new Node(0);
            Node* current = dummy;
            Node* original = head;

            // Traverse the original list to create the copied list
            while (original != nullptr) {
                // Create a new node with the same value
                Node* copied = new Node(original->val);
                current->next = copied;

                // Map the original node to its copied node
                nodeMap[original] = copied;

                current = current->next;
                original = original->next;
            }

            // Reset pointers for traversal
            current = dummy->next;
            original = head;

            // Connect random pointers for the copied list using the map
            while (original != nullptr) {
                // Set random pointer for the copied node using the map
                current->random = nodeMap[original->random];

                current = current->next;
                original = original->next;
            }

            return dummy->next;
        }
};