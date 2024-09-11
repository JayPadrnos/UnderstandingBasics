class Solution {
public:
    int getSum(int a, int b) {
        while (b != 0) {
            int carry = (a & b) << 1; // calculate the carry
            a = a ^ b; // calculate sum without carry
            b = carry; // assign carry to b to be added in the next iteration
        }
        return a;
    }
};
