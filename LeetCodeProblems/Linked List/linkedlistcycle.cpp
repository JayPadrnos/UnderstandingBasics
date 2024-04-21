#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
    public:
        bool hasCycle(ListNode *head) {
            if (!head || !head->next) {
                return false; // No cycle if there are less than two nodes
            }

            ListNode *slow = head;
            ListNode *fast = head->next; // Start fast pointer one step ahead

            while (fast && fast->next) {
                if (slow == fast) {
                    return true; // Found a cycle
                }
                slow = slow->next;      // Move slow pointer by one step
                fast = fast->next->next; // Move fast pointer by two steps
            }

            return false;
        }
};