// Problem: Word Break
// Platform: NeetCode
// Link: https://neetcode.io/problems/word-break
// time complexity: O(n^3); Outer loop i: O(n) Inner loop j: O(n) ,s.substr(j, i-j) banate: O(n) (substring copy korte time lage)
// space complexity: O(n); where n is the length of the string. The algorithm uses a boolean array to store the results of subproblems.


/*
Verify koro s = "leetcode", wordDict = ["leet","code"] diye:
wordSet = {"leet", "code"}
n = 8
dp[0] = true

i=1: j=0: dp[0]=true, s.substr(0,1)="l" -> not in wordSet -> dp[1]=false

i=2,3: similarly no match -> dp[2],dp[3] = false

i=4: j=0: dp[0]=true, s.substr(0,4)="leet" -> IN wordSet! -> dp[4]=true, break

i=5,6,7: j=0..i-1 check, kono match nai (dp[j] true thakলেও substring wordSet e nai)
  -> dp[5],dp[6],dp[7] = false

i=8: j=0: dp[0]=true, s.substr(0,8)="leetcode" -> not in wordSet
     j=1..3: dp[j]=false, skip
     j=4: dp[4]=true, s.substr(4,4)="code" -> IN wordSet! -> dp[8]=true, break

return dp[8] = true ✅
*/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // wordDict ke unordered_set e convert korlam, jate substring check O(1) e hoy
        // (list e linear search korle onek slow hoto)
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        int n = s.size();
        // dp[i] = protham i ta character (s[0..i-1]) ke wordDict er word diye 
        //         completely bhanga jay kina (true/false)
        vector<bool> dp(n+1, false);
        
        // Base case: dp[0] = true
        // "empty string" ke amra trivially valid dhori - eta trick base case,
        // recurrence relation thik rakhar jonno lagbe
        dp[0] = true;
        
        // Outer loop: protita prefix length i (1 theke n) er jonno check korchi
        for(int i = 1; i <= n; i++)
        {
            // Inner loop: shob possible "split point" j try korchi
            // (mane s[0..j-1] ar s[j..i-1] duita part e bhaga)
            for(int j = 0; j < i; j++)
            {
                // Check koro:
                //   1) dp[j] true kina (mane s[0..j-1] already valid vabe bhanga geche)
                //   2) s[j..i-1] substring ta wordSet e ache kina
                // duitai true hole, dp[i] o true hobe
                if(dp[j] && wordSet.count(s.substr(j, i-j)))
                {
                    dp[i] = true;
                    // ei i er jonno ekbar true peye gele ar check korar dorkar nai
                    break;
                }
            }
        }
        // dp[n] e thakbe puro string 's' valid vabe bhanga jay kina
        return dp[n];
    }
};