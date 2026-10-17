// Time: O(n)  -> duita pass, protita n
// Space: O(1) -> output array bade extra shudhu suffix variable

/*
index: 0  1  2  3
nums:  1  2  3  4
Pass 1: prefix (bam theke dan), ans[i] = i er bamer gunfol

Start: ans = [1, 1, 1, 1]

i	Kaj	                                    ans
1	ans[1] = ans[0] * nums[0] = 1 * 1	    [1, 1, 1, 1]
2	ans[2] = ans[1] * nums[1] = 1 * 2	    [1, 1, 2, 1]
3	ans[3] = ans[2] * nums[2] = 2 * 3	    [1, 1, 2, 6]

Ekhon ans[i] e shudhu bamer gunfol ache. ans[0] = 1 (bamer kichu nei), ans[3] = 6 (1×2×3).

Pass 2: suffix (dan theke bam), suffix = i er daner gunfol

Start: suffix = 1, ans = [1, 1, 2, 6]

i	ans[i] *= suffix	suffix *= nums[i]	ans	            suffix
3	6 * 1 = 6	        1 * 4 = 4	        [1, 1, 2, 6]	4
2	2 * 4 = 8	        4 * 3 = 12	        [1, 1, 8, 6]	12
1	1 * 12 = 12	        12 * 2 = 24	        [1, 12, 8, 6]	24
0	1 * 24 = 24	        24 * 1 = 24	        [24, 12, 8, 6]	24

Final = [24, 12, 8, 6]  
*/

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        // ans[i] shuru te 1 (gunfoler "kichu nei" value)
        vector<int> ans(n, 1);
        // Pass 1: bam theke dan
        // ans[i] = i er BAMER shob element er gunfol
        // i = 0 er bamer kichu nei, tai ans[0] = 1 e thake, loop i = 1 theke
        for (int i = 1; i < n; i++)
        {
            ans[i] = ans[i - 1] * nums[i - 1];
        }
        // Pass 2: dan theke bam
        // suffix = i er DANER shob element er gunfol (shuru te kichu nei, tai 1)
        int suffix = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            ans[i] *= suffix;       // bamer gunfol * daner gunfol
            suffix *= nums[i];      // NOTE: ans[i] er PORE update, nahole nijer value gun hoye jabe
        }
        return ans;
    }
};