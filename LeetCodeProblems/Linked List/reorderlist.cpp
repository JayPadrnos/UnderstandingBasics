#include <iostream>

// Definition for singly-linked list.
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };


class Solution {
    public:
        void reorderList(ListNode* head) {
            if (!head || !head->next)
            return;
            
            // Step 1: find the middle of the list
            ListNode *slow = head;
            ListNode *fast = head;

            while (fast->next && fast->next->next) {
                slow = slow->next;
                fast = fast->next->next;
            }

            // 'slow' is now at the middle of the node
            ListNode *secondHalf = slow->next;
            slow->next = nullptr; // Split the list into two halves

            // Step 2: Reverse the second half
            ListNode *prev = nullptr;
            ListNode *curr = secondHalf;

            while (curr) {
                ListNode *nextNode = curr->next;
                curr->next = prev;
                prev = curr;
                curr = nextNode;
            }

            secondHalf = prev; // 'secondHalf' is now the head of the reversed list

            // Step 3 Merge two halves
            ListNode *p1 = head;
            ListNode *p2 = secondHalf;

            while (p1 && p2) {
                ListNode *next1 = p1->next;
                ListNode *next2 = p2->next;

                p1->next = p2;
                p2->next = next1;

                p1 = next1;
                p2 = next2;
            }
        }
};