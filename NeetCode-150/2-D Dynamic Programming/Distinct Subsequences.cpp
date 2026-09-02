// Problem: Distinct Subsequences
// Platform: NeetCode
// Link:  https://neetcode.io/problems/distinct-subsequences
// time complexity: O(m × n); দুইটা nested loop — i যায় 1 থেকে m, j যায় 1 থেকে n.. প্রতিটা cell এ constant work
// space complexity: O(m × n); dp array এর size (m+1) × (n+1)

/*
দুইটা string s আর t দেওয়া আছে। s থেকে কয়টা distinct subsequence বানানো যায় যেইটা exactly t এর সমান — এই count বের করতে হবে।
উদাহরণ: s = "rabbbit", t = "rabbit" → answer হবে 3 (তিন রকম ভাবে s থেকে character বাদ দিয়ে t বানানো যায়, কারণ s তে তিনটা 'b' আছে, তার মধ্যে যেকোনো ২টা রাখলেই t বানানো যায়)

ধরি:
s = "babgbag"
t = "bag"
আমাদের কাজ হলো: s থেকে কিছু character বাদ দিয়ে কয়ভাবে "bag" বানানো যায়।

1️⃣ DP এর meaning - dp[i][j]
মানে: s এর প্রথম iটা character ব্যবহার করে t এর প্রথম jটা character কয়ভাবে বানানো যায়।

আমাদের strings
s = b a b g b a g
    1 2 3 4 5 6 7
t = b a g
    1 2 3
2️⃣ DP Table এর structure
        ""   b   a   g
      ----------------
""  |    1   0   0   0
b   |    1
a   |    1
b   |    1
g   |    1
b   |    1
a   |    1
g   |    1
কেন প্রথম column সবসময় 1? dp[i][0] = 1;
কারণ empty string ("") বানানোর একটা উপায় সবসময় আছে:
👉 সব character skip করে দেওয়া।

3️⃣ এখন একটা একটা করে দেখি প্রথম character: s[0] = 'b'
আমরা "b" বানাতে চাই।
s = "b"
t = "b"

Character match করেছে:

s[i-1] == t[j-1]
তাই:

dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
অর্থাৎ:

dp[1][1] = dp[0][0] + dp[0][1]
         = 1 + 0
         = 1
কারণ:
এই b টা use করে "b" বানানো যায় → 1 way
skip করলে আগের empty s দিয়ে "b" বানানো যায় না → 0 way

Table:

        ""   b   a   g
      ----------------
""  |    1   0   0   0
b   |    1   1   0   0

4️⃣ দ্বিতীয় character: s = "ba"
এখন s এর character হলো a।
আমরা "b" বানাতে চাই。

a != b

তাই a কে skip করতে হবে।
dp[2][1] = dp[1][1]
         = 1

কারণ আগের "b" দিয়েই "b" বানানো যাচ্ছিল। এখন "ba" বানাতে চাই।

a == a
Match!

dp[2][2] = dp[1][1] + dp[1][2]

অর্থাৎ:

= 1 + 0
= 1
এই 2টা অংশের meaning: dp[1][1]

বর্তমান a কে use করলাম। আগের "b" দিয়ে "b" বানাতে হবে。
b + a = ba
একটা way。

dp[1][2]

বর্তমান a কে skip করলাম。আগের "b" দিয়ে "ba" বানানোর চেষ্টা → possible না।

Table এখন:

        ""   b   a   g
      ----------------
""  |    1   0   0   0
b   |    1   1   0   0
a   |    1   1   1   0

5️⃣ সবচেয়ে important part: Match হলে 2টা choice

ধরি এখন আবার একটা b পেলাম।
s = "bab"

আমরা "b" বানাতে চাই। শেষের b এবং target এর b match করেছে।
এখন আমাদের দুইটা choice আছে।

Choice 1: নতুন b টা use করি
ba[b]
  ↑
use
Choice 2: নতুন b টা skip করি

আগের প্রথম b দিয়েই "b" বানানো হয়েছিল।

তাই:
dp[3][1] = dp[2][0] + dp[2][1]
         = 1 + 1
         = 2

এখন "bab" থেকে "b" বানানোর 2টা way:

1. [b]ab
2. ba[b]

এই জন্যই match হলে:

dp[i][j] = dp[i-1][j-1] + dp[i-1][j];

6️⃣ পুরো table fill করলে

শেষ পর্যন্ত table হবে:

          ""   b   a   g
        ----------------
""      |  1   0   0   0
b       |  1   1   0   0
ba      |  1   1   1   0
bab     |  1   2   1   0
babg    |  1   2   1   1
babgb   |  1   3   1   1
babgba  |  1   3   4   1
babgbag |  1   3   4   5

শেষের:
dp[7][3] = 5

মানে:

"babgbag" থেকে "bag" বানানোর 5টা distinct subsequence আছে。

7️⃣ আসলে সেই 5টা way কী?
b a b g b a g

bag বানানোর possible ways:

1. b a     g
   ↑ ↑     ↑

2. b a         g
   ↑ ↑         ↑

3. b     a     g
   ↑     ↑     ↑

4.     b   a   g
       ↑   ↑   ↑

5.     b     a g
       ↑     ↑ ↑

Character position আলাদা হলে সেটাকে আলাদা subsequence/way ধরা হয়।

🔥 সবচেয়ে important formula
যখন match করে
if(s[i-1] == t[j-1])
{
    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
}
এখানে:

dp[i-1][j-1]
বর্তমান character USE করছি

s[i-1] = t[j-1]

তাই দুটো string থেকেই এক character করে কমে যায়।

dp[i-1][j]
বর্তমান s[i-1] SKIP করছি

তাই শুধু s এক character কমে যায়, কিন্তু t একই থাকে।

যখন match করে না
else
{
    dp[i][j] = dp[i-1][j];
}

কারণ current s character দিয়ে target character বানানো সম্ভব না।

তাই বাধ্য হয়ে:
s[i-1] skip করতে হবে।
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        
        // dp[i][j] = s er prothom i characters use kore, t er prothom j characters koyvabe (koyta distinct subsequence hisebe) banano jay
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        // base case: t er 0 characters (empty string) banano'r way = 1 (kono character na niyei — empty subsequence shobshomoy valid)
        for(int i=0; i<=m; i++)
        {
            dp[i][0]=1;
        }
        // dp[0][j>0] automatically 0 thakbe (default init) - s theke kichu na niye, t er kono non-empty part banano shomvhob na
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(s[i-1] == t[j-1])
                {
                    // match korle 2ta possibility:
                    // 1. ei s[i-1] ke use kori t[j-1] er sathe match korte -> dp[i-1][j-1]
                    // 2. ei s[i-1] ke skip kori (onno kono match use korবো) -> dp[i-1][j]
                    // duitai alada "way", tai jog korlam
                    dp[i][j]=dp[i-1][j-1]+dp[i-1][j];
                }
                else
                {
                    // match na korle, s[i-1] ke obossoi skip korte hobe (t er ei character dorkar nai ekhon)
                    dp[i][j]=dp[i-1][j];
                }
            }
        }
        // full s (m characters) diye, full t (n characters) koyvabe banano jay - shei final answer
        return dp[m][n];
    }
};