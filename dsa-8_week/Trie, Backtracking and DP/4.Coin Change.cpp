// Time: O(S · n). Prottek i (1..S) e n ta coin try kori.
// Space: O(S), dp array.


/*
Dry run: coins = [1, 3, 4], amount = 6

Shuru: dp = [0, inf, inf, inf, inf, inf, inf] (index 0..6)

i	coin 1	        coin 3	        coin 4	        dp[i]
1	dp[0]+1 = 1	    1-3<0 skip	    skip	        1
2	dp[1]+1 = 2	    1-2<0 skip	    skip	        2
3	dp[2]+1 = 3	    dp[0]+1 = 1	    skip	        1
4	dp[3]+1 = 2	    dp[1]+1 = 2	    dp[0]+1 = 1	    1
5	dp[4]+1 = 2	    dp[2]+1 = 3	    dp[1]+1 = 2	    2
6	dp[5]+1 = 3	    dp[3]+1 = 2	    dp[2]+1 = 3	    2

Final: dp = [0, 1, 2, 1, 1, 2, 2], tai return 2 (3 + 3).  
*/


class Solution
{
public:
    int coinChange(vector<int>& coins, int amount)
    {
        int inf = 1e9;                        // "ekhono banano jay ni" bujhate boro value. 1e9 dile dp[i-c]+1 e overflow hoy na (INT_MAX dile hoto)
        vector<int> dp(amount + 1, inf);      // dp[x] = x taka banate sobcheye kom coin. size amount+1, karon index 0 theke amount porjonto lagbe. shuru te sob inf (impossible)
        dp[0] = 0;                            // 0 taka banate 0 coin lage. ei base case chhara kono dp[x] shuru-i hoy na
        for (int i = 1; i <= amount; i++)     // 1 theke amount porjonto, chhoto amount age, boro amount pore (chhoto answer age ready thakbe)
        {
            for (int c : coins)               // i banate "last coin" hishebe prottek coin try kori
            {
                if (i - c >= 0)               // coin c i er cheye boro hole use kora jay na, ar dp[negative] e crash korto
                {
                    dp[i] = min(dp[i], dp[i - c] + 1);   // c ke last coin dhorle baki i-c, tar answer dp[i-c], sathe 1 ta coin. ager best er sathe min nao
                }
            }
        }
        if (dp[amount] == inf)                // ekhono inf mane kono coin combination diye banano jay ni
            return -1;                        // problem er niyom: impossible hole -1
        else
            return dp[amount];                // noile sobcheye kom coin count
    }
};