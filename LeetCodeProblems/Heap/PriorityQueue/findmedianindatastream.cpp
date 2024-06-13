#include <queue>
#include <vector>

class MedianFinder {
    private:
        std::priority_queue<int> left_half; // Max-heap
        std::priority_queue<int, std::vector<int>, std::greater<int>> right_half; // Min-Heap


    public:
        MedianFind() {
        }

        void addNum(int num) {
            if (left_half.empty() || num <= left_half.top()) {
                left_half.push(num);
            } else {
                right_half.push(num);
            }

            // Balance the heaps
            if (left_half.size() > right_half.size() + 1) {
                right_half.push(left_half.top());
                left_half.pop();
            } else if (right_half.size() > left_half.size()) {
                left_half.push(right_half.top());
                right_half.pop();
            }
        }

        double findMedian() {
            if (left_half.size() > right_half.size()) {
                return left_half.top();
            } else {
                return (left_half.top() + right_half.top()) / 2.0;
            }
        }
};