class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();

        // Traverse from the last digit to the first.
        for (int i = n - 1; i >= 0; --i) {
            if (digits[i] < 9) {
                // If current digit is less than 9, increment it and return.
                digits[i]++;
                return digits;
            }
            // If current digit is 9, set it to 0.
            digits[i] = 0;
        }

        // If we exited the loop, it means all the digits were 9.
        // We need to add a 1 at the beginning.
        digits.insert(digits.begin(), 1);
        return digits;
    }
};
