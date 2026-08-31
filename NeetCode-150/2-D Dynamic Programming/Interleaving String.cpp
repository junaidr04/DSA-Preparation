// Problem: Interleaving String
// Platform: NeetCode
// Link:  https://neetcode.io/problems/interleaving-string
// time complexity: O(m × n); দুইটা nested loop — i যায় 1 থেকে m, j যায় 1 থেকে n.. প্রতিটা cell এ constant work
// space complexity: O(m × n) — for the DP table; dp array এর size (m+1) × (n+1)

/*
Example: s1 = "ab", s2 = "bc", s3 = "babc"

প্রথমে চেক করি length: s1.length() + s2.length() = 2 + 2 = 4, আর s3.length() = 4 ✓ (মিলে গেছে, তাই এগোতে পারি)

dp table বানাই

Size = (m+1) x (n+1) = 3 x 3 (m=2, n=2)

dp[i][j] মানে: "s1 এর প্রথম i characters + s2 এর প্রথম j characters মিলিয়ে, s3 এর প্রথম i+j characters বানানো সম্ভব কিনা"

Base case
cpp
dp[0][0] = true;

(কিছুই না নিয়ে, s3 এর 0 characters বানানো — trivially true)

Table ভরি ধাপে ধাপে (i=0 থেকে m, j=0 থেকে n)
i=0, j=0

dp[0][0] = true (base case, আগেই সেট করা)

i=0, j=1
i>0? না (i=0), তাই option 1 skip
j>0 ও s2[0]='b' == s3[0+1-1]=s3[0]='b'? হ্যাঁ, মিলছে!
dp[0][1] = dp[0][1] || dp[0][0] = false || true = true

(মানে: শুধু s2 থেকে 'b' নিয়ে, s3 এর প্রথম 1 character 'b' বানানো সম্ভব ✓)

i=0, j=2
option 1 skip (i=0)
s2[1]='c' == s3[0+2-1]=s3[1]='a'? না, মিলে না
dp[0][2] থেকে যায় false
i=1, j=0
s1[0]='a' == s3[1+0-1]=s3[0]='a'? হ্যাঁ!
dp[1][0] = dp[1][0] || dp[0][0] = false || true = true
option 2 skip (j=0)
i=1, j=1
s1[0]='a' == s3[1+1-1]=s3[1]='a'? হ্যাঁ!
dp[1][1] = dp[1][1] || dp[0][1] = false || true = true
s2[0]='b' == s3[1]='a'? না, মিলে না (এইটা skip, dp[1][1] আগের true-ই থাকবে)
i=1, j=2
s1[0]='a' == s3[1+2-1]=s3[2]='b'? না
s2[1]='c' == s3[2]='b'? না
dp[1][2] থাকে false
i=2, j=0
s1[1]='b' == s3[2+0-1]=s3[1]='a'? না
dp[2][0] থাকে false
i=2, j=1
s1[1]='b' == s3[2+1-1]=s3[2]='b'? হ্যাঁ!
dp[2][1] = dp[2][1] || dp[1][1] = false || true = true
s2[0]='b' == s3[2]='b'? হ্যাঁ!
dp[2][1] = dp[2][1] || dp[2][0] = true || false = true (already true, থাকলো true)
i=2, j=2
s1[1]='b' == s3[2+2-1]=s3[3]='c'? না
s2[1]='c' == s3[3]='c'? হ্যাঁ!
dp[2][2] = dp[2][2] || dp[2][1] = false || true = true
Final Table
i\j	0	1	2
i=0	T	T	F
i=1	T	T	F
i=2	F	T	T

Answer = dp[2][2] = true

হাতে verify করি

s1="ab", s2="bc" মিলিয়ে "babc" বানানো যায় কিনা:

b(s2) + a(s1) + b(s1) + c(s2) = "b-a-b-c" = "babc" ✓

আসলেই সম্ভব! s2 থেকে প্রথমে 'b' নাও, তারপর s1 থেকে "ab" পুরাটা নাও, তারপর s2 থেকে বাকি 'c' নাও — order ঠিক থাকছে দুই string এরই ভিতরে, তাই valid interleaving।
*/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        // prothome length check: s3 er length na mille, interleaving.. shomvhob e na, tai shurutei false
        if(m+n != s3.size())
            return false;
        
        // dp[i][j] = s1 er prothom i characters ar s2 er prothom j, characters mixe, s3 er prothom (i+j) characters banano 
        // shomvhob kina (true/false)
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        
        // base case: dujon theke e kichu na niye, s3 er 0 characters 
        // banano - eita trivially true (khali string = khali string)
        dp[0][0] = true;
        
        for(int i=0; i<=m; i++)
        {
            for(int j=0; j<=n; j++)
            {
                // (i=0, j=0) case e nicher duita if e dhoka jabe na 
                // (i>0 ar j>0 duitai false), tai dp[0][0]=true e thake jabe, thik ache
                // option 1: shesh character (s3[i+j-1]) ki s1 theke ashse?
                if(i > 0 && s1[i-1] == s3[i+j-1])
                {
                    // jodi match kore, tahole "baki অংশ" (s1 er age er 
                    // i-1 character, s2 er shob j character) age theke 
                    // valid chilo kina check kori (dp[i-1][j])
                    dp[i][j] = dp[i][j] || dp[i-1][j];
                }
                
                // option 2: shesh character ki s2 theke ashse?
                if(j > 0 && s2[j-1] == s3[i+j-1])
                {
                    // jodi match kore, "baki অংশ" (s1 er shob i character, 
                    // s2 er age er j-1 character) age theke valid chilo kina
                    dp[i][j] = dp[i][j] || dp[i][j-1];
                }
                // dujon theke e kono na miললে, dp[i][j] false e thake jabe 
                // (default value)
            }
        }
        // full s1 (m characters) ar full s2 (n characters) mixe 
        // pura s3 banano shomvhob kina
        return dp[m][n];
    }
};