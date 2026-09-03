// Problem: Edit Distance
// Platform: NeetCode
// Link:  https://neetcode.io/problems/edit-distance
// time complexity: O(m × n); দুইটা nested loop — i যায় 1 থেকে m, j যায় 1 থেকে n.. প্রতিটা cell এ constant work
// space complexity: O(m × n); dp array এর size (m+1) × (n+1)


/*
word1 = "cat"
word2 = "cut"
আমাদের goal: cat → cut

আমাদের string
word1 = c a t
        1 2 3

word2 = c u t
        1 2 3

DP table:
        ""   c   u   t
      ----------------
""   |
c    |
a    |
t    |

2️⃣ Base Case
word1 → empty string
যদি:
"cat" → ""
সব character delete করতে হবে।

"c"   → "" = 1 delete
"ca"  → "" = 2 delete
"cat" → "" = 3 delete

তাই:
dp[i][0] = i;
Empty string → word2
যদি:

"" → "cut"
তাহলে character insert করতে হবে।

"" → "c"   = 1 insert
"" → "cu"  = 2 insert
"" → "cut" = 3 insert

তাই:
dp[0][j] = j;

এখন table:

        ""   c   u   t
      ----------------
""   |  0   1   2   3
c    |  1
a    |  2
t    |  3

3️⃣ এখন i = 1, j = 1
আমরা compare করছি:

word1[0] = c
word2[0] = c
দুটো match করেছে ✅
তাই:

dp[1][1] = dp[0][0];
dp[1][1] = 0

কারণ:
"c" → "c"
কোনো operation লাগে না।

Table:

        ""   c   u   t
      ----------------
""   |  0   1   2   3
c    |  1   0
a    |  2
t    |  3

4️⃣ এখন i = 1, j = 2
Compare:
word1 prefix = "c"
word2 prefix = "cu"
Current character:
c != u

তাই 3টা operation consider করবো।

Option 1: Replace
Replace = dp[i-1][j-1]
        = dp[0][1]
        = 1
তারপর current operation replace করার জন্য:

1 + 1 = 2
Option 2: Delete
dlt = dp[i-1][j]
    = dp[0][2]
    = 2
current delete:
2 + 1 = 3
Option 3: Insert
Insert = dp[i][j-1]
       = dp[1][1]
       = 0
একটা character insert:
0 + 1 = 1
Minimum: min(2, 3, 1) = 1
তাই:
dp[1][2] = 1

কারণ:
"c" → "cu"
শুধু u insert করলেই হবে।

এখন সবচেয়ে important part
i = 2, j = 2

আমরা compare করছি:
word1 prefix = "ca"
word2 prefix = "cu"

Current characters:
a != u
তাই আবার 3টা option।

1. Replace
Replace = dp[1][1] = 0
মানে:
আগে:

"c" → "c"

convert করতে 0 operation লেগেছে।
এখন:
a → u
replace করবো।

Total = 0 + 1 = 1
2. Delete
dlt = dp[1][2] = 1

তারপর a delete:

Total = 1 + 1 = 2
3. Insert
Insert = dp[2][1]

এটা পরে table থেকে পাওয়া যাবে, ধরি value = 1।
তাহলে:
Total = 1 + 1 = 2

Minimum:min(1, 2, 2) = 1

তাই:
dp[2][2] = 1
বাস্তবে:

ca
↓ replace a → u
cu
মাত্র 1 operation।

5️⃣ পুরো DP Table

শেষ পর্যন্ত পুরো table হবে:

          ""   c   u   t
        ----------------
""      |  0   1   2   3
c       |  1   0   1   2
a       |  2   1   1   2
t       |  3   2   2   1

শেষের answer:
dp[3][3] = 1

অর্থাৎ:

cat → cut
Minimum operation = 1

তোমার 3টা operation আসলে কীভাবে কাজ করে?

ধরি:

word1 = "ca"
word2 = "cu"
শেষের:

a != u

তখন:

🟢 Replace
ca
 ↓
cu

a কে u বানিয়ে দাও।
Code: Replace = dp[i-1][j-1];

কারণ দুইটা current character-এর কাজ শেষ।

তাই:

word1 থেকে পিছনে যাই → i-1
word2 থেকেও পিছনে যাই → j-1
🔴 Delete

word1 এর current character delete করি:

ca → c

তাই word1 ছোট হয়ে যায়:

dlt = dp[i-1][j];
i কমে যায়
j একই থাকে
🔵 Insert

word1 এ word2[j-1] insert করি।

তাই target-এর একটা character match হয়ে যায়।

Insert = dp[i][j-1];

এখানে:

i একই
j কমে যায়
মনে রাখার সবচেয়ে সহজ trick =

যখন:

word1[i-1] != word2[j-1]

তখন:

Replace → ↖ dp[i-1][j-1]
Delete  → ↑ dp[i-1][j]
Insert  → ← dp[i][j-1]

Visual:

           dp[i-1][j-1]
                 ↖
                  Replace

dp[i][j-1]  ←  dp[i][j]  ↑ dp[i-1][j]
   Insert                   Delete

তারপর:

dp[i][j] = 1 + min({
    dp[i-1][j-1],  // Replace
    dp[i-1][j],    // Delete
    dp[i][j-1]     // Insert
});
এক লাইনে logic: Match করলে diagonal value নাও। Match না করলে Replace, Delete, Insert—এই 3টা option-এর minimum + 1 নাও।
*/

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        // dp[i][j] = word1 er prothom i characters ke word2 er prothom 
        // j characters e convert korte minimum koyta operation lagbe
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        // base case: word1 er i characters ke empty string banate exactly i ta delete lagbe
        for(int i=0; i<=m; i++)
        {
            dp[i][0]=i;
        }
        // base case: empty string theke word2 er j characters banate exactly j ta insert lagbe
        for(int j=0; j<=n; j++)
        {
            dp[0][j]=j;
        }
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(word1[i-1] == word2[j-1])
                {
                    // character match kore, kono operation lagবে na ei 
                    // position e, tai baki prefix er answer e ei answer
                    dp[i][j]=dp[i-1][j-1];
                }
                else
                {
                    // match na korle 3ta option:
                    // Replace: word1[i-1] ke word2[j-1] banai, tarpor duitar age er prefix ki obostay chilo
                    int Replace=dp[i-1][j-1];
                    
                    // Delete: word1[i-1] mucha feli, word2 er ei character dorkar nai ekhon
                    int dlt=dp[i-1][j];
                    
                    // Insert: word1 er ei position e notun character boshai jeta word2[j-1] er sathe mile
                    int Insert=dp[i][j-1];
                    
                    // tinটার moddhe minimum nilam, +1 (ei operation ta korar jonno)
                    dp[i][j]=1+min({Replace,dlt, Insert});
                }
            }
        }
        // full word1 ke full word2 e convert korte minimum operation
        return dp[m][n];
    }
};