#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    public:
        ListNode* removeNthFromEnd(ListNode* head, int n) {
            // Creat a dummy node to handle edge cases
            ListNode* dummy = new ListNode(0);
            dummy->next = head;

            ListNode* fast = dummy; // Pointer to move n+1 steps ahead
            ListNode* slow = dummy; // Pointer to reach the previous node of the target

            // Move the fast pointer n+1 steps ahead
            for (int i = 0; i < n + 1; ++i) {
                if (fast == nullptr) {
                    // Handle cases where n is greater than the length of the list
                    return head;
                }
                fast = fast->next;
            }

            // Move both pointers until fast reaches the end
            while (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }

            // Remove the nth node from the end
            slow->next = slow->next->next;

            return dummy->next; // return the updated head
        }
};