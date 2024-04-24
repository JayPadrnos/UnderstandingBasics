#include <queue>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    public:
        ListNode* mergeLists(vector<ListNode*>& lists) {
            // Custom comparator for min-heap (priority queue)
            auto cmp = [](const ListNode* a, const ListNode* b) {
                return a->val > b->val; // Min-heap based on node values
            };

            // Priority queue to hold the heads of each list
            priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

            // Initialize the priority queue with the heads of each list
            for (ListNode* list : lists) {
                if (list) {
                    pq.push(list);
                }
            }

            // Dummy node to simplify merging process
            ListNode dummy(0);
            ListNode* tail = &dummy;

            // Merge process
            while (!pq.empty()) {
                // Extract the smallest node from the heap
                ListNode* smallest = pq.top();
                pq.pop();

                // Append the smallest node to the merged list
                tail->next = smallest;
                tail = tail->next;

                // Move the pointer in the original list forward
                if (smallest->next) {
                    pq.push(smallest->next);
                }
            }

            return dummy.next; // Head of the merged sorted list
        }
};