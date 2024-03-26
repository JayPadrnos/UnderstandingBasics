#include <stack>
#include <climits>

class MinStack {
    private:
        std::stack<int> stack; // Stack to store elements
        std::stack<int> minStack; // Stack to store minimum elements

    public:
        MinStack() {}

        void push (int val) {
            stack.push(val);
            // Update minStack if the newly pushed value is 
            if (minStack.empty() || val <= minStack.top()) {
                minStack.push(val);
            }
        }

        void pop() {
            if (!stack.empty()) {
                // If the popped element is the current minimum, pop from minStack as well
                if (stack.top() == minStack.top()) {
                    minStack.pop();
                }
                stack.pop();
            }
        }

        int top () {
            if (!stack.empty()) {
                return stack.top();
            }
            return INT_MIN; // Assuming  INT_MIN as a sentinel value for an empty stack
        }

        int getMin() {
            if (!minStack.empty()) {
                return minStack.top();
            }
            return INT_MIN; // Assuming INT_MIN as a sentinel value for an empty stack
        }
};


#include <iostream>
    int main() {
        MinStack minStack;
        minStack.push(-2);
        minStack.push(0);
        minStack.push(-3);
        std::cout << minStack.getMin() << std::endl; // Output: -3
        minStack.pop();
        std::cout << minStack.top() << std::endl; // Output: 0
        std::cout << minStack.getMin() << std::endl; // Output: -2
        return 0;
    }


   /* class MinStack {
public:
    MinStack() {
        
    }
    
    void push(int val) {
        
    }
    
    void pop() {
        
    }
    
    int top() {
        
    }
    
    int getMin() {
        
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */