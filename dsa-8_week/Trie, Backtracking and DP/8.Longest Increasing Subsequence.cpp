// Time: O(n²). Duto nested loop, prottek ta n bar.
// Space: O(n), dp array.

/*
nums = [3, 1, 2]

Shuru: dp = [1, 1, 1], ans = 1

i	nums[i]	j	        nums[j]	 nums[i] > nums[j]?	    dp[i]
0	3	    (j nai)			                            1
1	1	    0	        3	     1 > 3 na, skip	        1
2	2	    0	        3	     2 > 3 na, skip	        1
2	2	    1	        1	     2 > 1 ha, dp[1]+1 = 2	2

ans update: max(1,1)=1, max(1,1)=1, max(1,2)=2. Return 2 ([1, 2]).
*/


class Solution
{
public:
    int lengthOfLIS(vector<int>& nums)
    {
        int n = nums.size();                      
        // dp[i] = index i e SHESH hoy emon sobcheye lomba increasing subsequence er length
        // shuru te sob 1, karon prottek element nijei ekta sequence (length 1)
        vector<int> dp(n, 1);
        int ans = 1;                              // sobcheye lomba length. kom pokkhe 1 (n >= 1 hole)
        for (int i = 0; i < n; i++)               // i = ekhon kon element e sequence shesh korchi
        {
            for (int j = 0; j < i; j++)           // j = i er pichone (age) thaka prottek element
            {
                if (nums[i] > nums[j])            // j chhoto, i boro (strictly), tahole j er pore i boshano jay
                {
                    // j e shesh howa sequence er shesh e i jog korle length = dp[j] + 1
                    // onek j thakle sobcheye boro ta nao, tai max
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);                // i e shesh howa sequence ta ager best er cheye lomba kina dekho
                                                  // j loop er baire, karon dp[i] puro final howar por compare korbo
        }
        return ans;                              
    }
};