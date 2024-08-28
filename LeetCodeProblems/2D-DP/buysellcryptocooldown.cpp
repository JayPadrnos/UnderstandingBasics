class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        vector<int> hold(n, 0); // Maximum profit if holding a NeetCoin at day i
        vector<int> cash(n, 0); // Maximum profit if not holding a NeetCoin at day i

        hold[0] = -prices[0]; // If we buy on the first day

        for (int i = 1; i < n; ++i) {
            hold[i] = max(hold[i-1], (i >= 2 ? cash[i-2] : 0) - prices[i]);
            cash[i] = max(cash[i-1], hold[i-1] + prices[i]);
        }

        return cash[n-1];
    }
};
