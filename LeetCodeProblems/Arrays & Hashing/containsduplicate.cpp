// Brute Force
// Time complexity  O((n*(n+1))/2) ≈ O(n^2)
// Space complexity O(1)
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        bool flag = false;
        for(int i = 0; i < nums.size(); i++){
            for(int j = i + 1; j < nums.size(); j++){
                if(nums[i] == nums [j]) return true;
            }
        }
        return flag;
    }
};

// Shortened Approach
// Time complexity  O(n*log(n))
// Space complexity O(1)
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        bool flag = false;
        for(int i = 0; i < nums.size() - 1; i++){
            if(nums[i] == nums [i+1]) return true;
        }
        return flag;
    }
};

// Set approach
// Time Complexity  O(n*log(n))
// Space Complexity O(n)
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        return nums.size() > set<int>(nums.begin(), nums.end()).size();
    }
};

// Map
// Time Complexity  O(n*log(n))
// Space Complexity O(n)
class Solutions {
public:
    bool containsDuplicate(vectore<int>& nums) {
        map<int,int> mp;
        for(auto i : nums) mp[i]++;
        bool flag = false;
        for(auto i : mp){
            if(i.second>= 2) return true;
        }
        return flag;
    }
};

// Hashmap
// Time complexity  O(n)
// Space complexity O(n)
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,int> mp;
        for(auto i : nums) mp[i]++;
        bool flag = false;
        for(auto i : mp){
            if(i.second >= 2) return true;
        }
        return flag;
    }
};

// ChatGPT solution to make more efficient
class Solution {
public:
    bool containsDuplicate(const std::vector<int>& nums) {
        std::unordered_set<int> unique_elements;
        
        for (int num : nums) {
            auto [it, inserted] = unique_elements.emplace(num);
            if (!inserted) {
                // Duplicate found
                return true;
            }
        }

        // No duplicates found
        return false;
    }
};
