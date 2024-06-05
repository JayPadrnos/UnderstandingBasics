#include <vector>
#include <queue>
using namespace std;

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) : k(k) { // Initialize k here
        for (int num : nums) {
            add(num);
        }
    }
    
    int add(int val) {
        if (minHeap.size() < k) {
            minHeap.push(val);
        } else if (val > minHeap.top()) {
            minHeap.pop();
            minHeap.push(val);
        }
        return minHeap.top();
    }

private:
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int k;
};

// Example usage
// int main() {
//     vector<int> nums = {1, 2, 3, 3};
//     KthLargest kthLargest(3, nums);
//     cout << kthLargest.add(3) << endl;  // Output: 3
//     cout << kthLargest.add(5) << endl;  // Output: 3
//     cout << kthLargest.add(6) << endl;  // Output: 3
//     cout << kthLargest.add(7) << endl;  // Output: 5
//     cout << kthLargest.add(8) << endl;  // Output: 6
// }