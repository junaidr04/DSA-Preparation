// Problem: Target Sum
// Platform: NeetCode
// Link:  https://neetcode.io/problems/target-sum
// time complexity: O(n × newTarget); দুইটা nested loop — i যায় 1 থেকে n, j_remain যায় 0 থেকে newTarget.. প্রতিটা cell এ constant work
// space complexity: O(n × newTarget) — for the DP table; dp array এর size (n+1) × (newTarget+1)



//Example: nums = [0, 0, 1], target = 1

class Solution
{
public:
    int findTargetSumWays(vector<int>& nums, int target)
    {
        int n = nums.size(); // n = 3 (koyta number ache, seita gonlam)
        // shob number jog korlam: total = 0+0+1 = 1
        int totalSum = 0;
        for(int num : nums)
        {
            totalSum += num;
        }
        
        // sum(P) - sum(N) = target, ar sum(P) + sum(N) = totalSum..ei duita equation shomadhan korle: sum(P) = (totalSum + target) / 2
        // tai amader "positive set" er sum ber korte hobe, seita e newTar..jodi (totalSum + target) odd hoy, tahole integer division e 
        // valid subset sum shomvhob na, tai 0 return
        if((totalSum + target) % 2 != 0) // (1+1) % 2 = 0, tai eita fail korlo na, egiye jai
            return 0;
        
        // target er absolute value totalSum er cheye boro hole, eito target e pouchano shomvhobই na (max possible sum e totalSum)
        if(abs(target) > totalSum) // abs(1) = 1, total = 1, 1 > 1? na, tai eitao pass
            return 0;
        int newTar = (totalSum + target) / 2; // newTar = (1+1)/2 = 1.. mane: amader ekhon khujte hobe koyta subset ache jar sum = 1
        
        // dp[i][s] = prothom i ta number use kore, sum ঠিক s banano'r ..koyta way ache
        vector<vector<int>> dp(n+1, vector<int>(newTar+1)); // dp table banalam, size (3+1) x (1+1) = 4 x 2... dp[i][j] = prothom i ta number diye sum=j banano'r koyta way
        
        // base case: 0 sum banano'r shomoy always 1 way (kono number na niye)
        dp[0][0] = 1; // base case: 0 ta number use kore (kono number e nai), sum=0 banano'r 1 way.. (eita e ekmatro explicit base case, baki shob recurrence e compute hobe)
        // dp[0][s>0] automatically 0 thakbe (default vector initialization)
        for(int i = 1; i <= n; i++)
        {
            for(int j_remain = 0; j_remain <= newTar; j_remain++)
            {
                if((j_remain - nums[i-1]) >= 0)
                {
                    // option 1: skip kori ei number -> dp[i-1][j_remain]
                    // option 2: include kori (positive set e dilam) -> dp[i-1][j_remain - nums[i-1]]
                    // kheyal koro duitai i-1 (0/1 knapsack, ekbar-i use hoy,unbounded na, tai same row e jai na)
                    dp[i][j_remain] = dp[i-1][j_remain] + dp[i-1][j_remain-nums[i-1]];                
                }
                else
                {
                    // ei number ta current sum er cheye boro, fit e kore na
                    // tai age er row er value e thakbe
                    dp[i][j_remain] = dp[i-1][j_remain];
                }
            }
        }
/*
Table বানাই ধাপে ধাপে
Initial state (base case বসানোর পর):

i\j	0	1
i=0	1	0
i=1	?	?
i=2	?	?
i=3	?	?
i=1 (nums[0] = 0)
j_remain=0: 0 - 0 = 0 ≥0 → dp[0][0] + dp[0][0-0] = dp[0][0] + dp[0][0] = 1 + 1 = 2 (এইখানেই "zero doubling" effect দেখো — যেহেতু nums[0]=0, j_remain আর j_remain - nums[0] একই index, তাই তুমি নিজের value নিজের সাথেই যোগ করছো, effectively double করে ফেলছো!)
j_remain=1: 1 - 0 = 1 ≥0 → dp[0][1] + dp[0][1] = 0 + 0 = 0

Row i=1: [2, 0]

i=2 (nums[1] = 0)
j_remain=0: dp[1][0] + dp[1][0] = 2 + 2 = 4
j_remain=1: dp[1][1] + dp[1][1] = 0 + 0 = 0

Row i=2: [4, 0]

i=3 (nums[2] = 1)
j_remain=0: 0 - 1 = -1 <0 → else branch → dp[2][0] = 4
j_remain=1: 1 - 1 = 0 ≥0 → dp[2][1] + dp[2][0] = 0 + 4 = 4

Row i=3: [4, 4]

Final table
i\j	0	1
i=0	1	0
i=1	2	0
i=2	4	0
i=3	4	4
*/
    return dp[n][newTar]; // dp[3][1] = 4
    }
};