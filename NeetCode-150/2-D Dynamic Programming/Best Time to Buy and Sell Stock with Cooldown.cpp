// Problem: Best Time to Buy and Sell Stock with Cooldown
// Platform: NeetCode
// Link: https://neetcode.io/problems/longest-common-subsequence/question
// time complexity: O(n); Unique states = (i, holding) → i এর n+1 টা possible value, holding এর 2 টা → total 2(n+1) unique states ,প্রতিটা state memoization এর কারণে exactly একবার compute হয়, প্রতিবার constant work (O(1))..তাই total TC = O(n) — brute force এর O(2^n) থেকে অনেক কমে গেলো
// space complexity: O(n); memo array এর size (n+1) × 2 → O(n) space, Recursion call stack এর depth ও max O(n) হতে পারে (i প্রতি call এ অন্তত ১ বাড়ে)

class Solution
{
public:
    // memo[i][holding] = day i te, holding state e thakle,
    // shamne theke maximum ki profit pawa jabe
    // class member hishebe rakhlam, karon recursion e protibar
    // function call hole eita reset hobe na (state maintain hobe)
    vector<vector<int>> memo;

    int solve(int i, int holding, vector<int> &prices)
    {
        // base case: din shesh hoye gele, ar kono extra profit hobe na
        if (i >= prices.size())
            return 0;

        // memo check: ei (i, holding) state age compute kora hoyeche kina
        // hoye thakle, abar recursion na kore direct shei value ferot dilam
        if (memo[i][holding] != -1)
            return memo[i][holding];
        int result;
        if (holding) // aajke amar kache stock ache
        {
            // choice 1: aajke SELL kori
            // profit e prices[i] jog hobe, sell korar por cooldown (i+2 e jai)
            // cooldown er por hand e stock thakbe na (holding = false)
            int sell = prices[i] + solve(i + 2, false, prices);

            // choice 2: kichu na kore HOLD kori
            // kono taka jog/biyog hobe na, porer din o holding = true thakbe
            int hold = solve(i + 1, true, prices);
            // dutar moddhe beshi ta nilam
            result = max(sell, hold);
        }
        else // aajke amar kache stock nai
        {
            // choice 1: aajke BUY kori
            // taka kharoch hocche, tai -prices[i]
            // buy korar por cooldown nai, porer din e holding = true hoye jabe
            int buy = solve(i + 1, true, prices) - prices[i];
            // choice 2: kichu na kore WAIT kori
            // kono taka jog/biyog nai, porer din o holding = false thakbe
            int wait = solve(i + 1, false, prices);
            // dutar moddhe beshi ta nilam
            result = max(buy, wait);
        }
        // ei (i, holding) state er answer ta memo te store kore rakhlam
        // jate porer bar eki state e call ashle recompute na lage
        memo[i][holding] = result;
        return result;
    }

    int maxProfit(vector<int> &prices)
    {
        // memo array initialize korlam
        // size: (n+1) rows (day 0 theke n porjonto, base case shoho)
        //       2 columns (holding = false=0 ba true=1)
        // shob cell -1 diye bhorlam, mane "ekhono compute hoyni"
        memo.assign(prices.size() + 1, vector<int>(2, -1));
        // day 0 theke shuru, ekhono kono stock kena hoyni (holding = false)
        return solve(0, false, prices);
    }
};