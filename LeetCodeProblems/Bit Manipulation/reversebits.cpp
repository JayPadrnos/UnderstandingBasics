class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t reversed = 0;
        for (int i = 0; i < 32; ++i) {
            // Extract the least significant bit of n
            uint32_t current_bit = n & 1;
            // Shift reversed to the left and add the current bit
            reversed = (reversed << 1) | current_bit;
            // Shift n to the right for the next bit
            n >>= 1;
        }
        return reversed;
    }
};
