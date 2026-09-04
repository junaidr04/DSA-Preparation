// Problem: Regular Expression Matching
// Platform: NeetCode
// Link: https://neetcode.io/problems/regular-expression-matching/question
// time complexity: O(m × n); 
// space complexity: O(m × n); 



/*
আমাদের কাছে:
s = "aa"
p = ".b"
আমাদের দেখতে হবে পুরো s string টা পুরো p pattern-এর সাথে match করে কিনা।

Pattern: .b
Pattern-এ দুইটা অংশ আছে:

.   b
. এর অর্থ কী?

. যেকোনো একটি character match করতে পারে।

তাই:

s = "aa"
p = ".b"

এখন এক এক করে match করি 👇

s	p	Match?
a	.	✅ কারণ . যেকোনো character match করে
a	b	❌ কারণ a != b

s = "nnn"
p = "n*"

আমরা জানি:

* = আগের character-কে 0 বা তার বেশি বার match করতে পারে

এখানে *-এর আগের character হলো:

n*
↑
আগের element

Example:

s = "nnn"
p = "n*"

প্রথমে:

s = n n n
    0 1 2 3

p = n *
    0 1 2

তাই:
m = 3
n = 2

DP table হবে:

        ""    n    *
""      ?     ?    ?
n       ?     ?    ?
n       ?     ?    ?
n       ?     ?    ?

অর্থাৎ 4 × 3 table।

3. প্রথমে dp[0][0]
dp[0][0] = true;

মানে:

s = ""
p = ""

দুটোই empty।

তাই:

dp[0][0] = true

Table:

        ""     n      *
""      T      F      F
n       F      F      F
n       F      F      F
n       F      F      F

4. dp[0][j] calculation

Pattern:
p = "n*"
j = 2 হলে:

p[j-1]
= p[1]
= '*'

তাই: dp[0][2] = dp[0][0];
অর্থাৎ:dp[0][2] = true
কেন?
কারণ:

s = ""
p = "n*"

এখানে n* বলতে 0টা n নেওয়া যায়।

তাই match:

"" = ""

Table:

        ""     n      *
""      T      F      T
n       F      F      F
n       F      F      F
n       F      F      F

5. এবার i = 1, j = 1

বর্তমান:
s[i-1] = s[0] = 'n'
p[j-1] = p[0] = 'n'

তাই: s[i-1] == p[j-1]

অর্থাৎ:
'n' == 'n'

✅ Match

তাই:dp[1][1] = dp[0][0];

আর: dp[0][0] = true

তাই: dp[1][1] = true

Table:

        ""     n      *
""      T      F      T
n       F      T      F
n       F      F      F
n       F      F      F
6. i = 1, j = 2

এখন:

s[i-1] = s[0] = 'n'
p[j-1] = p[1] = '*'

তাই * case-এ ঢুকবে।

প্রথম possibility: zero occurrence dp[i][j] = dp[i][j-2];
মানে:

dp[1][2] = dp[1][0]

dp[1][0] মানে:
s = "n"
p = ""

এটা match করবে না।

তাই: dp[1][0] = false

সুতরাং:
dp[1][2] = false
এবার one-or-more

* এর আগের character:

p[j-2]
= p[0]
= 'n'

Current s character:
s[i-1] = 'n'

তাই: 'n' == 'n'
✅ Match
তখন:

dp[1][2] = dp[1][2] || dp[0][2];

আমরা জানি:

dp[1][2] = false
dp[0][2] = true

তাই: false || true = true

অর্থাৎ: dp[1][2] = true

মানে:

s = "n"
p = "n*"

match করে।

কারণ: n* → n

Table:

        ""     n      *
""      T      F      T
n       F      T      T
n       F      F      F
n       F      F      F

7. i = 2, j = 1

এখন:
s[i-1] = s[1] = 'n'
p[j-1] = p[0] = 'n'

Match: 'n' == 'n'

তাই: dp[2][1] = dp[1][0]

কিন্তু: dp[1][0] = false

তাই: dp[2][1] = false
কারণ "nn" কে শুধু "n" দিয়ে match করা যায় না।

8. i = 2, j = 2

এখন আবার *।

s[i-1] = 'n'
p[j-1] = '*'
Zero occurrence
dp[2][2] = dp[2][0]

এটা false।

One/more occurrence

আগের character: p[j-2] = 'n'
Current: s[i-1] = 'n'

Match ✅

তাই: dp[2][2] = dp[2][2] || dp[1][2]

আমরা জানি:

dp[2][2] = false
dp[1][2] = true

তাই: false || true = true

অর্থাৎ: dp[2][2] = true

এখানে বুঝতে পারো:
n* → nn

9. i = 3, j = 2
শেষ character:

s[2] = 'n'

Pattern: p[1] = '*'
আবার: n* → nnn

Zero occurrence: dp[3][0] = false
One/more: dp[2][2] = true

তাই:
dp[3][2]= false || true = true

10. Final DP Table

শেষে পুরো table:

          ""      n       n*
        ┌───────┬───────┬───────┐
""      │   T   │   F   │   T   │
        ├───────┼───────┼───────┤
"n"     │   F   │   T   │   T   │
        ├───────┼───────┼───────┤
"nn"    │   F   │   F   │   T   │
        ├───────┼───────┼───────┤
"nnn"   │   F   │   F   │   T   │
        └───────┴───────┴───────┘

শেষে আমরা চাই: dp[m][n]

এখানে:
m = 3
n = 2

তাই:
dp[3][2] = true
সুতরাং: return true;
*/

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        // s and p এর length বের করছি
        int m = s.size(), n = p.size();
        // DP table বানাচ্ছি
        // dp[i][j] মানে:
        // s-এর প্রথম i টি character p-এর প্রথম j টি character দিয়ে match করে কিনা
        // তাই size হবে:(m+1) x (n+1)
        // +1 কারণ 0 character-এর case-ও রাখতে হবে
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, false));
        // দুটোই empty হলে অবশ্যই match করবে, s = "", p = "" তাই true
        dp[0][0] = true;
        // Empty string s-এর সাথে pattern match করাচ্ছি
        // j = 2 থেকে শুরু কারণ '*' একা থাকতে পারে না
        // '*' এর আগে একটা character থাকবেই
        for(int j = 2; j <= n; j++)
        {
            // যদি current pattern character '*'
            if(p[j - 1] == '*')
            {
                // x* কে zero বার ব্যবহার করলে x এবং * দুটোই বাদ যাবে
                // তাই j-2 position-এর result দেখছি
                dp[0][j] = dp[0][j - 2];
            }
        }
        // s-এর প্রতিটা character নিয়ে কাজ করছি
        // i = 1 → s-এর প্রথম character
        // i = 2 → s-এর প্রথম 2টা character
        // ...
        for(int i = 1; i <= m; i++)
        {
            // p-এর প্রতিটা character নিয়ে কাজ করছি
            for(int j = 1; j <= n; j++)
            {

                // CASE 1:
                // Current character সরাসরি match করছে কিনা দেখি
                // দুইভাবে match হতে পারে:
                // 1. s[i-1] == p[j-1] যেমন: 'a' == 'a'
                // 2. p[j-1] == '.' , '.' যেকোনো একটি character match করতে পারে
                if(s[i - 1] == p[j - 1] || p[j - 1] == '.')
                {
                    // Current দুইটা character match করেছে, তাই আগের অংশ match করেছিল কিনা দেখি
                    // s-এর একটা character বাদ → i-1 , p-এর একটা character বাদ → j-1
                    dp[i][j] = dp[i - 1][j - 1];
                }
                // CASE 2: Current pattern character '*'
                else if(p[j - 1] == '*')
                {
                    // প্রথম possibility:
                    // '*' → zero occurrence
                    // যেমন: a* → "" তাই 'a' এবং '*' দুটোই বাদ দিতে হবে j থেকে 2 ঘর পিছনে
                    dp[i][j] = dp[i][j - 2];
                    // দ্বিতীয় possibility:
                    // '*' → one or more occurrence
                    // কিন্তু সেটা করার আগে দেখতে হবে s-এর current character কি
                    // '*' এর আগের character-এর সাথে match করে কিনা, '*' আছে p[j-1]-এ
                    // তাই '*' এর আগের character p[j-2]
                    if(s[i - 1] == p[j - 2] || p[j - 2] == '.')
                    {
                        // Match করলে current s character consume করছি
                        // কিন্তু pattern-এর j একই রাখছি
                        // কারণ '*' আরও character নিতে পারে তাই dp[i-1][j]
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }
        // পুরো s এবং পুরো p match করেছে কিনা সেটাই final answer dp[m][n]
        return dp[m][n];
    }
};