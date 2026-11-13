// Time: O(n²·L) (i, j duto loop, prottek e substr toiri o hash e O(L) bar O(n) porjonto). Optimize: j ke i - L er niche jete na dile O(n·L²).
// Space: O(n + W·L), dp array ar dictionary set.


/*
Dry run: s = "abc", wordDict = ["a", "bc"]

Shuru: dp = [T, F, F, F] (index 0..3)

i	j	dp[j]	s.substr(j, i-j)	dict e ache?	dp[i]
1	0	T	    "a"	                ache	        T (break)
2	0	T	    "ab"	            nai	
2	1	T	    "b"	                nai	            F
3	0	T	    "abc"	            nai	
3	1	T	    "bc"	            ache	        T (break)
3	2				                                (break hoye gese)

Final: dp = [T, T, F, T], return dp[3] = true.
*/

class Solution
{
public:
    bool wordBreak(string s, vector<string>& wordDict)
    {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());   // dictionary ke set e rakhi, jate "ache kina" O(1) e check kora jay
        int n = s.size();          
        // dp[i] = s er prothom i ta akkhor dictionary er word diye bhag kora jay kina
        // size n+1, karon i = 0 (khali) theke i = n (puro string) porjonto lagbe
        vector<bool> dp(n + 1, false);            // shuru te shob false, ekhono kono prefix bhag kora jay ni
        dp[0] = true;                             // ager bar false chhilo. khali string bhag korte kichu lage na, eta base case
        for (int i = 1; i <= n; i++)              // i = prefix er length (1 theke n)
        {
            for (int j = 0; j < i; j++)           // j = kothay theke "shesh tukro" shuru hobe
            {
                // shorto 1: dp[j], prothom j ta akkhor age thekei bhag kora jay
                // shorto 2: s[j .. i-1] tukro ta dictionary te ache
                if (dp[j] && dict.count(s.substr(j, i - j)))
                {
                    dp[i] = true;                 // prothom i ta akkhor bhag kora jay
                    break;                        // break jog korlam. ekbar true hoye gele aro j dekhar dorkar nai
                }
            }
        }
        return dp[n];                             // ager bar false chhilo. puro string (n ta akkhor) bhag kora jay kina
    }
};