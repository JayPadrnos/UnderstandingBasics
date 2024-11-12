#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
    public:
        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
            // Dummy node to start the merged list
            ListNode* dummy = new ListNode(-1);
            ListNode* current = dummy;

            // Traverse both lists
            while (list1 != nullptr && list2 != nullptr) {
                if (list1->val <= list2->val) {
                    current->next = list1;
                    list1 = list1->next;
                } else {
                    current->next = list2;
                    list2 = list2->next;
                }
                current = current->next;
            }

            // Append remaining nodes if any 
            if (list1 != nullptr) {
                current->next = list1;
            } else {
                current->next = list2;
            }

            // Store the head of the merged list
            ListNode* mergedHead = dummy->next;
            delete dummy; // free dummy node

            return mergedHead;  
        }
};