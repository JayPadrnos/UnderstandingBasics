#include <vector>
#include <limits>

class Solution {
    public:
        int maxProfit(std::vector<int>& prices) {
            int minPrice = std::numeric_limits<int>::max();
            int maxProfit = 0 ;

            for (int price : prices) {
                // Update minPrice to track the lowest price encountered so far
                minPrice = std::min(minPrice, price);

                // Calculate potential profit if selling at the current price
                int currentProfit = price - minPrice;

                // Update maxProfit to the max of currentProfit and the existing maxProfit
                maxProfit = std::max(maxProfit, currentProfit);
            }

            return maxProfit;
        }
};