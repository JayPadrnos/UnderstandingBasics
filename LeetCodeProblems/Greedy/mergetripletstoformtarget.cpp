class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        // Flags to check if we've seen a valid triplet for each component of the target
        bool found_a = false, found_b = false, found_c = false;

        // Iterate over each triplet
        for (auto& triplet : triplets) {
            // Check if the current triplet can be used to reach the target
            if (triplet[0] <= target[0] && triplet[1] <= target[1] && triplet[2] <= target[2]) {
                // Update flags based on which components match the target
                if (triplet[0] == target[0]) found_a = true;
                if (triplet[1] == target[1]) found_b = true;
                if (triplet[2] == target[2]) found_c = true;
            }
        }

        // If all components can be matched, return true
        return found_a && found_b && found_c;
    }
};
