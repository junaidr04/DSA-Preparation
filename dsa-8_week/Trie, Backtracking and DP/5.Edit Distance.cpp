// Time: O(m · n). Table e (m+1)·(n+1) cell, prottek cell e O(1) kaj.
// Space: O(m · n) (2D table). Optimize kore O(n) kora jay, karon dp[i][j] shudhu ager row (i-1) ar nijer row dekhe.

/*
word1 = "horse", word2 = "ros"

Base case (prothom row/column):

          ""   r   o   s
   ""      0   1   2   3
   h       1
   o       2
   r       3
   s       4
   e       5

Ekhon ek ek row bhori:

          ""   r   o   s
   ""      0   1   2   3
   h       1   1   2   3
   o       2   2   1   2
   r       3   2   2   2
   s       4   3   3   2
   e       5   4   4   3

Kichu cell er hishab:

dp[1][1] (h vs r): min(dp[0][1]=1, dp[1][0]=1, dp[0][0]=0) + 1 = 1
dp[2][2] (o vs o): mile gelo, dp[1][1] = 1, tai 1
dp[3][1] (r vs r): mile gelo, dp[2][0] = 2, tai 2
dp[4][3] (s vs s): mile gelo, dp[3][2] = 2, tai 2
dp[5][3] (e vs s): min(dp[4][3]=2, dp[5][2]=4, dp[4][2]=3) + 1 = 3

Final: dp[5][3] = 3. (horse -> rorse -> rose -> ros.)
*/

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int m = word1.size(), n = word2.size(); // m = word1 er length, n = word2 er length
        // dp[i][j] = word1 er prothom i ta char ke word2 er prothom j ta char banate sobcheye kom step
        // size (m+1) x (n+1), karon i=0 (khali string) theke i=m (puro string) porjonto lagbe
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // Prothom column (j = 0): word2 khali. word1 er i ta char ke khali banate i ta DELETE lage
        for (int i = 0; i <= m; i++)
        {
            dp[i][0] = i;
        }
        // Prothom row (i = 0): word1 khali. word2 er j ta char banate j ta INSERT lage
        for (int j = 0; j <= n; j++)
        {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; i++) // word1 er prottek prefix length
        {
            for (int j = 1; j <= n; j++) // word2 er prottek prefix length
            {
                // dp er i-th char mane string er index i-1 (karon dp te extra "khali" row/column ache)
                if (word1[i - 1] == word2[j - 1])
                {
                    // Character mile gele kono step lagbe na, duto-i ek ghor pichone giye jai
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    // Na mile 3 ta choice er sobcheye kom ta + 1 ta step
                    dp[i][j] = 1 + min({
                                       dp[i - 1][j],    // upore: DELETE word1[i-1] (word1 er 1 char kome, word2 same)
                                       dp[i][j - 1],    // bame: INSERT word2[j-1] (word1 same, word2 er 1 char match hoye gelo)
                                       dp[i - 1][j - 1] // tirjok: REPLACE word1[i-1] ke word2[j-1] diye (duto-i 1 char kome)
                                   });                  // FIX: ager bar min(a,b,c) chhilo, ekhon min({a,b,c})
                }
            }
        }
        return dp[m][n]; // puro word1 (m char) ke puro word2 (n char) banate koto step
    }
};