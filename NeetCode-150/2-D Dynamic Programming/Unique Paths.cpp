// Problem: Unique Paths
// Platform: NeetCode
// Link: https://neetcode.io/problems/count-paths/question
// time complexity: O(m * n); দুইটা nested loop চালাইছো, i যায় 1 থেকে m-1, j যায় 1 থেকে n-1..প্রতিটা cell এ constant work (একটা addition) হচ্ছে..তাই total operations ≈ m × n
// space complexity: O(m * n); dp array এর size m × n, প্রতিটা cell store করে রাখতে হচ্ছে.. এইটাই extra space যা তুমি ব্যবহার করছো (input ছাড়া)

class Solution {
public:
    int uniquePaths(int m, int n) {
        // dp[i][j] = (i,j) cell e pouchanor koyta unique way ache..প্রথমে shob cell 1 diye initialize korlam
        // কারণ প্রথম row (i=0) আর প্রথম column (j=0) এর way সবসময় 1.. (khali right e right e ba down e down e giye pouchano jay)
        vector<vector<int>> dp(m, vector<int>(n, 1));
        // i=1, j=1 theke শুরু করলাম, কারণ প্রথম row/column already handled
        for(int i = 1; i < m; i++)
        {
            for(int j = 1; j < n; j++)
            {
                // (i,j) e pouchanor way = upor theke asha way (dp[i-1][j]) +  baam theke asha way (dp[i][j-1])
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        // bottom-right corner e pouchanor total way ta e final answer
        return dp[m-1][n-1];
    }
};