class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> output(n + 1);
        output[0] = 0; // Base case, 0 has 0 bits set to 1.
        
        for (int i = 1; i <= n; ++i) {
            if (i % 2 == 0) {
                // i is even, number of 1's is same as i/2.
                output[i] = output[i / 2];
            } else {
                // i is odd, number of 1's is same as i/2 plus 1.
                output[i] = output[i / 2] + 1;
            }
        }
        
        return output;
    }
};
