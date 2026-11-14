// Time: O(m · n), table e (m+1)·(n+1) cell, prottek cell e O(1) kaj.
// Space: O(m · n). Shudhu ager row lage, tai O(min(m, n)) kora jay.


/*
text1 = "abcde", text2 = "ace"

Shuru: prothom row ar column shob 0.

          ""   a   c   e
   ""      0   0   0   0
   a       0   1   1   1
   b       0   1   1   1
   c       0   1   2   2
   d       0   1   2   2
   e       0   1   2   3

Kichu cell er hishab:

dp[1][1] (a vs a): mile gelo, 1 + dp[0][0] = 1
dp[2][1] (b vs a): mile na, max(dp[1][1]=1, dp[2][0]=0) = 1
dp[3][2] (c vs c): mile gelo, 1 + dp[2][1] = 2
dp[4][2] (d vs c): mile na, max(dp[3][2]=2, dp[4][1]=1) = 2
dp[5][3] (e vs e): mile gelo, 1 + dp[4][2] = 3

Final: dp[5][3] = 3. Common subsequence "ace".  
*/

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();   // m = text1 er length, n = text2 er length
        // dp[i][j] = text1 er prothom i ta char ar text2 er prothom j ta char er LCS (sobcheye lomba common subsequence) er length
        // size (m+1) x (n+1), karon i=0 / j=0 (khali string) o lagbe
        // shuru te sob 0: khali string er sathe kono char common hoy na, tai prothom row/column alada likhte hoy ni
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++)              // text1 er prottek prefix length (1 theke m)
        {
            for (int j = 1; j <= n; j++)          // text2 er prottek prefix length (1 theke n)
            {
                // dp er i-th char mane string er index i-1 (karon dp te extra "khali" row/column ache)
                if (text1[i - 1] == text2[j - 1])
                {
                    // char mile gele common subsequence er length 1 bare
                    // duto string theke ei char duto bad dile baki ongsho er LCS = dp[i-1][j-1], tar sathe +1
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                {
                    // char mile na, tahole duto choice:
                    //   dp[i-1][j]: text1 er ei char ta bad dilam
                    //   dp[i][j-1]: text2 er ei char ta bad dilam
                    // LCS lomba chai, tai joto boro ta, max nao (Edit Distance e min chhilo)
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];                          // puro text1 (m char) ar puro text2 (n char) er LCS
    }
};