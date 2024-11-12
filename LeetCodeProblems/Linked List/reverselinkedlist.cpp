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
        ListNode* reverseList(ListNode* head) {
            ListNode* prev = nullptr;
            ListNode* current = head;
            ListNode* next = nullptr;

            while (current != nullptr) {
                // Store the next node
                next = current->next;
                // Reverse the link
                current->next = prev;
                // Move pointers one position ahead
                prev = current;
                current = next;
            }

            // After loop, 'prev' will be the new head of the reversed list
            return prev;
        }
};

// Utility function to print the linked list
void printList(listNode* head) {
    ListNode* temp = head;
    while (temp != nullptr) {
        std::cout << temp->val << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

int main() {
    // Example usage
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    Solution sol;
    std::cout << "Original list: ";
    printList(head);

    ListNode* reversedHead = sol.reversList(head);

    std::cout << "Reversed list: ";
    printList(reversedHead);

    return 0;
}