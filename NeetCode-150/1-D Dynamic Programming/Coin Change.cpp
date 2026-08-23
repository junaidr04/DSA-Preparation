// Problem: Coin Change
// Platform: NeetCode
// Link: https://neetcode.io/problems/coin-change
// time complexity: O(n * m); where n is the amount and m is the number of coin denominations. The nested loop iterates through each amount and each coin denomination.
// space complexity: O(n); where n is the amount. The dp array stores the minimum number of coins needed for each amount from 0 to the target amount.

/*
Problem Statement

Tomake ekটা array coins[] deya ache (different coin denominations), ar ekটা target amount deya ache। Tomake বের korতে হবে minimum koto গুলো coin লাগবে ei amount banate। Jদি কোনোভাবেই banano na jায়, তাহলে -1 return korবে।

Note: Protিটা coin যতবার খুশি use korা jাবে (unlimited supply)।

Example:

coins = [1,2,5], amount = 11
Output: 3

Explanation: 11 = 5 + 5 + 1 (3 ta coin)
coins = [2], amount = 3
Output: -1

Explanation: 2 diye kokhono 3 banano jাবে না (2, 4, 6... shob even hবে)
coins = [1], amount = 0
Output: 0

Explanation: 0 amount banate 0 ta coin lagবে
Key Insight

Eটা Min Cost Climbing Stairs er khুব কাছাকাছি — kিন্তু এখানে duটো step (1 ba 2) er বদলে, প্রতিটা coin denomination ekটা "step" er মতো কাজ করে, ar তুমি যেকোনো coin বেছে নিতে পারো (শুধু 2 টা fixed option না, বরং coins.size() টা option)।

Nijeke jiggasha koro
State ki? — dp[i] মানে কি? (Hint: "amount i বানাতে minimum কত গুলো coin লাগবে")
Transition ki? — dp[i] কে কিভাবে বের করবে? তুমি প্রতিটা coin এর জন্য চেক করবে — যদি coin <= i হয়, তাহলে dp[i - coin] + 1 ekটা সম্ভাব্য answer (mane oi coin ekটা use kore, বাকিটা আগেই solve করা আছে ধরে নাও)। সব coin এর মধ্যে যেটা minimum, সেটাই dp[i]।
Base case ki? — dp[0] কত হবে? (Hint: 0 amount বানাতে কয়টা coin লাগে?)
"Banano jায় na" কিভাবে বুঝবে? — শুরুতে সব dp[i] কে ekটা বড় value (jemon INT_MAX অথবা amount+1) দিয়ে initialize করো, jদি শেষ পর্যন্ত update না হয়, তাহলে বুঝবে ওই amount বানানো যায়নি।


Verify koro coins=[1,2,5], amount=11 diye:
dp[0] = 0
dp[1] = min over coins: coin=1(<=1,dp[0]=0valid)->dp[0]+1=1 ; coin=2,5 too big -> dp[1]=1
dp[2] = coin=1: dp[1]+1=2 ; coin=2: dp[0]+1=1 -> dp[2]=1
dp[3] = coin=1: dp[2]+1=2 ; coin=2: dp[1]+1=2 -> dp[3]=2
dp[4] = coin=1: dp[3]+1=3 ; coin=2: dp[2]+1=2 -> dp[4]=2
dp[5] = coin=1: dp[4]+1=3 ; coin=2: dp[3]+1=3 ; coin=5: dp[0]+1=1 -> dp[5]=1
dp[6] = coin=1: dp[5]+1=2 ; coin=2: dp[4]+1=3 ; coin=5: dp[1]+1=2 -> dp[6]=2
dp[7] = coin=1: dp[6]+1=3 ; coin=2: dp[5]+1=2 ; coin=5: dp[2]+1=2 -> dp[7]=2
dp[8] = coin=2: dp[6]+1=3 ; coin=5: dp[3]+1=3 ; coin=1: dp[7]+1=3 -> dp[8]=3
dp[9] = coin=5: dp[4]+1=3 -> dp[9]=3
dp[10] = coin=5: dp[5]+1=2 -> dp[10]=2
dp[11] = coin=1: dp[10]+1=3 ; coin=2: dp[9]+1=4 ; coin=5: dp[6]+1=3 -> dp[11]=3

return dp[11] = 3 ✅
*/

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        // dp[i] = amount i banate minimum koto ta coin lagbe...shuru te sob "infinity" (INT_MAX) diye initialize korlam, mane dhore nilam kono amount ekhono banano jaini
        vector<int> dp(amount + 1, INT_MAX);
        // Base case: dp[0] = 0.. 0 amount banate 0 ta coin lagbe (kono coin lagbe na)
        dp[0] = 0;
        // Outer loop: protita amount (1 theke target amount) er jonno..minimum coin calculate korchi
        for (int i = 1; i <= amount; i++)
        {
            // Inner loop: protita available coin denomination try korchi
            for (int coin : coins)
            {
                // Condition 1: coin ta current amount 'i' theke choto/shoman hote hobe
                //   (naile oi coin use kora jaবে na)
                // Condition 2: dp[i-coin] "infinity" na hoya lagbe
                //   (mane i-coin amount ta already valid vabe banano jay emon hote hobe,
                //    naile INT_MAX+1 kore integer overflow hoye jaবে)
                if (coin <= i && dp[i - coin] != INT_MAX)
                {
                    // ei coin use korle koto ta coin lagবে: dp[i-coin] + 1
                    // (age i-coin amount banate jotogula coin lেগেছিলো, তার সাথে ekটা এই coin)
                    // shob coin er modhe MINIMUM ta rakhi
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        // Loop shesh howar por check koro dp[amount] ekhono "infinity" ache kina..jodi thake, mane kono combination diye amount ta banano jayni
        if (dp[amount] == INT_MAX)
            return -1;
        // naile dp[amount] e thakবে minimum coin count - eitai answer
        return dp[amount];
    }
};