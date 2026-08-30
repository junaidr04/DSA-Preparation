// Problem: Coin Change II
// Platform: NeetCode
// Link: https://neetcode.io/problems/coin-change-ii
// time complexity: O(n * amount); Unique states = (i, remaining) → i এর n+1 টা possible value, remaining এর amount+1 টা → total (n+1)(amount+1) unique states ,প্রতিটা state memoization এর কারণে exactly একবার compute হয়, প্রতিবার constant work (O(1))..তাই total TC = O(n * amount) — brute force এর O(2^n) থেকে অনেক কমে গেলো
// space complexity: O(n * amount); dp array এর size (n+1) × (amount+1)


/*  
Calculation: coins = [1, 2, 5], amount = 5

Table size হবে (n+1) x (amount+1) = 4 x 6 (n=3 coins, amount=5)

Base case row/column ভরি (i=0 to 3, remaining=0 always 1):

i \ remaining	0	1	2	3	4	5
i=0 (কোনো coin না)	1	0	0	0	0	0
i=1 (coin=1)	1	?	?	?	?	?
i=2 (coin=1,2)	1	?	?	?	?	?
i=3 (coin=1,2,5)	1	?	?	?	?	?
Row i=1 (শুধু coin=1 available) ভরি

coins[0] = 1

dp[1][1]: 1-1=0 ≥0 → dp[0][1] + dp[1][0] = 0 + 1 = 1
dp[1][2]: 2-1=1 ≥0 → dp[0][2] + dp[1][1] = 0 + 1 = 1
dp[1][3]: 3-1=2 ≥0 → dp[0][3] + dp[1][2] = 0 + 1 = 1
dp[1][4]: 4-1=3 ≥0 → dp[0][4] + dp[1][3] = 0 + 1 = 1
dp[1][5]: 5-1=4 ≥0 → dp[0][5] + dp[1][4] = 0 + 1 = 1

(মানে শুধু coin 1 দিয়ে যেকোনো amount বানানোর 1 way — সবগুলা 1 বসিয়ে)

Row i=2 (coin=1,2 available) ভরি

coins[1] = 2

dp[2][1]: 1-2=-1 <0 → dp[1][1] = 1
dp[2][2]: 2-2=0 ≥0 → dp[1][2] + dp[2][0] = 1 + 1 = 2
dp[2][3]: 3-2=1 ≥0 → dp[1][3] + dp[2][1] = 1 + 1 = 2
dp[2][4]: 4-2=2 ≥0 → dp[1][4] + dp[2][2] = 1 + 2 = 3
dp[2][5]: 5-2=3 ≥0 → dp[1][5] + dp[2][3] = 1 + 2 = 3
Row i=3 (coin=1,2,5 available) ভরি

coins[2] = 5

dp[3][1]: 1-5=-4 <0 → dp[2][1] = 1
dp[3][2]: 2-5=-3 <0 → dp[2][2] = 2
dp[3][3]: 3-5=-2 <0 → dp[2][3] = 2
dp[3][4]: 4-5=-1 <0 → dp[2][4] = 3
dp[3][5]: 5-5=0 ≥0 → dp[2][5] + dp[3][0] = 3 + 1 = 4
Final table
i \ remaining	0	1	2	3	4	5
i=0	1	0	0	0	0	0
i=1	1	1	1	1	1	1
i=2	1	1	2	2	3	3
i=3	1	1	2	2	3	4

Answer = dp[3][5] = 4 ✓ (আগে discuss করা 4টা combination এর সাথে মিলে গেলো: {5}, {2,2,1}, {2,1,1,1}, {1,1,1,1,1})

কেন 2D লাগলো?

খেয়াল করো — শুধু remaining amount জানলেই চলতো না। একই remaining value এর জন্য answer আলাদা হতে পারে, কোন কোন coin এখনো "available" আছে তার উপর ভিত্তি করে।

উদাহরণ দেখো table থেকে:

dp[1][5] = 1 (শুধু coin=1 available থাকলে, remaining=5 এর answer 1)
dp[2][5] = 3 (coin=1,2 available থাকলে, remaining=5 এর answer 3)
dp[3][5] = 4 (coin=1,2,5 available থাকলে, remaining=5 এর answer 4)

same remaining=5, কিন্তু answer ভিন্ন ভিন্ন — কারণ "কোন coins ব্যবহার করার permission আছে" এইটাও state এর অংশ। যদি শুধু remaining রেখে 1D dp বানাতা (dp[remaining]), তাহলে conflict হয়ে যেতো — কোন value overwrite হবে বুঝা যেতো না।
*/

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        // dp[i][remaining] = prothom i ta coin type (unlimited bar use kore)
        // diye "remaining" amount banano'r koyta distinct way ache
        vector<vector<int>> dp(n+1, vector<int>(amount+1));
        // base case: remaining = 0 hole always 1 way ache 
        // (kono coin na niye — empty combination)
        for(int i = 0; i <= n; i++)
        {
            dp[i][0] = 1;
        }
        // note: dp[0][remaining>0] automatically 0 thakbe (default vector init),
        // karon kono coin na thakle positive amount banano possible na
        for(int i = 1; i <= n; i++)
        {
            for(int j_remain = 1; j_remain <= amount; j_remain++)
            {
                // ei coin (coins[i-1]) ta current remaining er moddhe fit kore kina check
                if(j_remain - coins[i-1] >= 0)
                {
                    // option 1: ei coin skip kori -> dp[i-1][j_remain] (age er coin set diye)
                    // option 2: ei coin ekbar use kori -> dp[i][j_remain - coins[i-1]]
                    //           (kheyal koro, i-1 na, i-tei thaklam, karon coin ta 
                    //            abar o use kora jabe — eita e "unbounded" trick)
                    // duita option er WAYS jog korlam (max na, karon amra total 
                    // combination count kortesi)
                    dp[i][j_remain] = dp[i-1][j_remain] + dp[i][j_remain - coins[i-1]];
                }
                else
                {
                    // coin ta boro, fit e kore na, tai age er row er value e thakbe
                    dp[i][j_remain] = dp[i-1][j_remain];
                }
            }
        }
        // shob n ta coin use kore, full amount banano'r total way
        return dp[n][amount];
    }
};