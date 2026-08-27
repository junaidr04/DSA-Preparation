// Problem: Longest Common Subsequence
// Platform: NeetCode
// Link: https://neetcode.io/problems/longest-common-subsequence/question
// time complexity: O(m * n); দুইটা nested loop চালাইছো, i যায় 1 থেকে m-1, j যায় 1 থেকে n-1..প্রতিটা cell এ constant work (একটা addition) হচ্ছে..তাই total operations ≈ m × n
// space complexity: O(m * n); dp array এর size m × n, প্রতিটা cell store করে রাখতে হচ্ছে.. এইটাই extra space যা তুমি ব্যবহার করছো (input ছাড়া)

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        // dp[i][j] = text1 er first i characters ar text2 er first j characters
        // er moddhe LCS koto boro hote pare
        // extra row/column (index 0) rakhlam "0 characters" case represent korte
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        
        for(int i = 1; i <= m; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                // i-1, j-1 use korlam কারণ dp 1-indexed, kintu string 0-indexed
                if(text1[i-1] == text2[j-1])
                {
                    // character match korle, ei character LCS er part hobe
                    // tai dujon-i ekta ager position theke +1 korlam
                    dp[i][j] = 1 + dp[i-1][j-1];
                }
                else
                {
                    // match na korle, ekjon ke ager position e rekhe..arekjon ke egiye niye best (max) ta nilam
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        // full text1 ar full text2 er moddhe LCS = dp[m][n]
        return dp[m][n];
    }
};