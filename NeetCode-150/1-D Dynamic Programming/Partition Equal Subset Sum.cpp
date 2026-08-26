// Problem: Partition Equal Subset Sum
// Platform: NeetCode
// Link: https://neetcode.io/problems/partition-equal-subset-sum
// time complexity: O(n^2); Outer loop i: O(n) Inner loop j: O(n)
// space complexity:

/*
nums = [1, 5, 11, 5], total = 1+5+11+5 = 22, target = 22/2 = 11
dp (initial) = [T, F, F, F, F, F, F, F, F, F, F, F]
Index:          0  1  2  3  4  5  6  7  8  9  10 11
num = 1 (reverse: i=11 theke 1)

শুধু i=1 e change হবে (কারণ dp[i-1] শুধু i=1 e (dp[0]=true) true পাওয়া যায়):

i=1: dp[1] = dp[1] || dp[0] = F || T = TRUE
dp = [T, T, F, F, F, F, F, F, F, F, F, F]

বুঝলে? — এখন sum=1 বানানো যায় (শুধু {1} নিয়ে)।

num = 5 (প্রথম 5) (reverse: i=11 theke 5)
i=11: dp[11] || dp[6] = F||F = F
i=10: dp[10] || dp[5] = F||F = F
i=9:  dp[9]  || dp[4] = F||F = F
i=8:  dp[8]  || dp[3] = F||F = F
i=7:  dp[7]  || dp[2] = F||F = F
i=6:  dp[6]  || dp[1] = F||TRUE = TRUE!
i=5:  dp[5]  || dp[0] = F||TRUE = TRUE!
dp = [T, T, F, F, F, T, T, F, F, F, F, F]

বুঝলে? — এখন sum=5 (শুধু {5}) ar sum=6 ({1,5}) দুটোই বানানো যায়।

num = 11 (reverse: i=11 theke 11)
i=11: dp[11] || dp[0] = F||TRUE = TRUE!
dp = [T, T, F, F, F, T, T, F, F, F, F, T]

বুঝলে? — শুধু {11} নিয়েই sum=11 পাওয়া গেলো!

num = 5 (দ্বিতীয় 5) (reverse: i=11 theke 5)
i=11: dp[11] || dp[6] = TRUE||TRUE = true (already true)
i=10: dp[10] || dp[5] = F||TRUE = TRUE!
i=9:  dp[9]  || dp[4] = F||F = F
i=8:  dp[8]  || dp[3] = F||F = F
i=7:  dp[7]  || dp[2] = F||F = F
i=6:  dp[6]  || dp[1] = TRUE||TRUE = true
i=5:  dp[5]  || dp[0] = TRUE||TRUE = true
dp = [T, T, F, F, F, T, T, F, F, F, T, T]
Final Result
dp[11] = TRUE ✅

Output: true — matches, কারণ {5,5,1} mile 11 hয়, ar বাকি {11} ও 11 হয়।  
*/

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // total sum ber koro
        int total = 0;
        for(int num : nums)
        {
            total += num;
        }
        // jodi total odd hoy, duita equal integer subset e bhaga jabe na
        if(total % 2 != 0)
            return false;
        // target = protita subset er sum ki hote hobe (total er odhek)
        int target = total / 2;
        // dp[i] = kono kichu elements bechhe niye sum 'i' banano jay kina
        vector<bool> dp(target+1, false);
        // sum 0 banate kono element lagbe na - trivially true
        dp[0] = true;
        // protita number ke ekbar kore consider korchi (0/1 Knapsack style)
        for(int num : nums)
        {
            // REVERSE loop - target theke num porjonto komte komte
            // eta joruri, karon amra chai protita element JUST EKBAR use hok
            // (forward loop korle same element multiple বার use hoye jete pare,
            //  jeta Coin Change e thik chilo, kintu ekhane allowed na)
            for(int i = target; i >= num; i--)
            {
                // dp[i] true hobe jodi already true thake, 
                // OTHOBA jodi 'num' bad diye baki (i-num) sum age theke banano jay
                dp[i] = dp[i] || dp[i-num];
            }
        }
        // target sum banano geche kina - eitai final answer
        return dp[target];
    }
};