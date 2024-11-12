class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) return 1;  // Base case: anything raised to the power of 0 is 1
        
        // Handle negative powers
        if (n < 0) {
            x = 1 / x;
            n = -n;
        }
        
        // Recursive approach
        double half = myPow(x, n / 2);
        
        // If n is even
        if (n % 2 == 0) {
            return half * half;
        } 
        // If n is odd
        else {
            return half * half * x;
        }
    }
};
