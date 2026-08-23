// Problem: Decode Ways
// Platform: NeetCode
// Link: https://neetcode.io/problems/decode-ways
// time complexity: O(n); Karon loop ekbar i=2 theke i=n-1 porjonto chole, mane total n-2 ≈ n iterations. Protita iteration e O(1) kaj hocche (shudhu addition and max), tai overall time complexity linear, O(n).
// space complexity: O(n); dp vector er size n+1। O(n) space।


/*
Problem Statement-

Ekটা mapping ache:

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
Tomake ekta string s deya ache, jetate শুধু digit (0-9) থাকবে। Tomake বের korte হবে koto রকম ভাবে ei string ke decode kora jai (mane koto গুলো valid letter-combination বানানো যায়)।

Example:

s = "12"
Output: 2

Explanation: "12" ke decode kora jায় duভাবে:
  "AB" (1=A, 2=B)
  "L" (12=L)
s = "226"
Output: 3

Explanation: 
  "BZ" (2=B, 26=Z)
  "VF" (22=V, 6=F)
  "BBF" (2=B, 2=B, 6=F)
s = "06"
Output: 0

Explanation: "0" দিয়ে কোনো valid letter শুরু হয় না (mane leading zero কে single digit হিসেবে decode করা যায় না), 
ar "06" ke duই digit hিসেবেo দেখলে সেটাও invalid (06 > 26 ar leading zero)। Tাi কোনো valid way নেই।

Verify koro s = "226" diye:
n = 3
dp[0] = 1
s[0]='2' != '0' -> dp[1] = 1

i=2 (s[1]='2'):
  s[1] != '0' -> dp[2] += dp[1] = 1  => dp[2]=1
  twoDigit = (s[0]-'0')*10+(s[1]-'0') = 2*10+2 = 22
  22 is between 10-26 -> dp[2] += dp[0] = 1 => dp[2]=2

i=3 (s[2]='6'):
  s[2] != '0' -> dp[3] += dp[2] = 2  => dp[3]=2
  twoDigit = (s[1]-'0')*10+(s[2]-'0') = 2*10+6 = 26
  26 is between 10-26 -> dp[3] += dp[1] = 1 => dp[3]=3

return dp[3] = 3 ✅

Match kore expected output er sathe!

Verify koro s = "06" diye (edge case):
n = 2
dp[0] = 1
s[0]='0' -> dp[1] = 0

i=2 (s[1]='6'):
  s[1] != '0' -> dp[2] += dp[1] = 0  => dp[2]=0
  twoDigit = (s[0]-'0')*10+(s[1]-'0') = 0*10+6 = 6
  6 is NOT between 10-26 -> skip

return dp[2] = 0 ✅ Match kore expected output er sathe!
*/

class Solution
{
public:
    int numDecodings(string s)
    {
        int n = s.size();
        
        // dp[i] = protham i ta character diye koto rokom vabe decode kora jay
        vector<int> dp(n+1, 0);
        
        // Base case: dp[0] = 1
        // "empty string" decode korar 1 ta way ache - kichu na kora
        // eta trick base case, recurrence relation thik rakhar jonno lagbe
        dp[0] = 1;
        
        // Base case: dp[1]
        // Protham character diye decode kora jay kina depend kore seta '0' kina tar upor
        if(s[0] == '0')
            dp[1] = 0;  // '0' diye kono valid letter shuru hoy na
        else
            dp[1] = 1;  // single valid digit, 1 ta way
        
        for(int i = 2; i <= n; i++)
        {
            // Option 1: last 1 ta digit alada kore decode kora
            // Valid hobe jodi oi digit '0' na hoy
            if(s[i-1] != '0')
            {
                dp[i] += dp[i-1];
            }
            
            // Option 2: last 2 ta digit eksathe decode kora
            // Duita digit mile ekta number banao
            int twoDigit = (s[i-2]-'0')*10 + (s[i-1]-'0');
            // Valid hobe jodi eta 10 theke 26 er modhe hoy
            // (10 er niche hole seta leading zero er problem, 26 er upore hole seta A-Z range er baire)
            if(twoDigit >= 10 && twoDigit <= 26)
            {
                dp[i] += dp[i-2];
            }
        }
        // dp[n] e thakbe pura string decode korar total ways
        return dp[n];
    }
};