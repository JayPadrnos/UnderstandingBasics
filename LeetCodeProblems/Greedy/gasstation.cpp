class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int total_gas = 0;
        int current_tank = 0;
        int start_index = 0;
        
        for (int i = 0; i < n; ++i) {
            int net_gas = gas[i] - cost[i];
            total_gas += net_gas;
            current_tank += net_gas;
            
            // If current tank is negative, reset and try next station as start
            if (current_tank < 0) {
                current_tank = 0;
                start_index = i + 1;
            }
        }
        
        // If total gas is less than zero, return -1
        if (total_gas < 0) {
            return -1;
        }
        
        return start_index;
    }
};
