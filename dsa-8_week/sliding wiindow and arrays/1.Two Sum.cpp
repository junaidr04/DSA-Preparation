// Time Complexity: O(n); 
// Space Complexity: O(n);


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // key = ager dekha value, value = tar index
        unordered_map<int, int> seen;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            // ei element er sathe jar jor milale target hobe
            int need = target - nums[i];
            // age check: need ager kono index e dekha hoyeche kina
            if (seen.find(need) != seen.end())
            {
                // paoa gele: ager index + current index
                return {seen[need], i};
            }
            // check er PORE insert, nahole nijer sathe nijei match hoye jabe
            seen[nums[i]] = i;
        }
        // kono pair na pele (problem guarantee dile unreachable)
        return {};
    }
};