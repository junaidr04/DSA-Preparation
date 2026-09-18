// Problem: Multiply Strings
// Platform: NeetCode
// Link: https://neetcode.io/problems/multiply-strings
// time complexity: O(m * n); দুই স্ট্রিংয়ের দৈর্ঘ্য m ও n
// space complexity: O(m + n); result স্ট্রিংয়ের জন্য

/*
Example diye calculation (num1 = "12", num2 = "34")

Expected: 12 × 34 = 408

n1 = 2, n2 = 2, ans size = n1+n2 = 4, শুরুতে ans = [0, 0, 0, 0] (index 0,1,2,3)

String indices: num1[0]='1', num1[1]='2', num2[0]='3', num2[1]='4'

i=1 (digit '2'), j=1 (digit '4'):

mul = 2×4 = 8
p1 = 1+1 = 2, p2 = 1+1+1 = 3
sum = 8 + ans[3] = 8 + 0 = 8
ans[3] = 8 % 10 = 8 → ans = [0,0,0,8]
ans[2] += 8/10 = 0 → ans = [0,0,0,8] (unchanged)

i=1 (digit '2'), j=0 (digit '3'):

mul = 2×3 = 6
p1 = 1+0 = 1, p2 = 1+0+1 = 2
sum = 6 + ans[2] = 6 + 0 = 6
ans[2] = 6 % 10 = 6 → ans = [0,0,6,8]
ans[1] += 6/10 = 0 → ans = [0,0,6,8] (unchanged)

i=0 (digit '1'), j=1 (digit '4'):

mul = 1×4 = 4
p1 = 0+1 = 1, p2 = 0+1+1 = 2
sum = 4 + ans[2] = 4 + 6 = 10
ans[2] = 10 % 10 = 0 → ans = [0,0,0,8]
ans[1] += 10/10 = 1 → ans = [0,1,0,8]

i=0 (digit '1'), j=0 (digit '3'):

mul = 1×3 = 3
p1 = 0+0 = 0, p2 = 0+0+1 = 1
sum = 3 + ans[1] = 3 + 1 = 4
ans[1] = 4 % 10 = 4 → ans = [0,4,0,8]
ans[0] += 4/10 = 0 → ans = [0,4,0,8] (unchanged)

Final ans = [0, 4, 0, 8]

String বানানো (leading zero skip):

num=0: res.empty()==true && num==0 → skip
num=4: skip condition false (num≠0) → res = "4"
num=0: res.empty() false → add হবে → res = "40"
num=8: → res = "408"

Output: "408" ✅ (12 × 34 = 408 ✓)
*/

class Solution
{
public:
    string multiply(string num1, string num2)
    {
        if (num1 == "0" || num2 == "0") return "0"; // edge case age handle koro
        int n1 = num1.size(), n2 = num2.size();
        vector<int> ans(n1 + n2, 0);                  // max possible digits eituku e hobe
        for (int i = n1 - 1; i >= 0; i--)             // num1 er right theke left
        {
            for (int j = n2 - 1; j >= 0; j--)         // num2 er right theke left
            {
                int mul = (num1[i] - '0') * (num2[j] - '0'); // duita digit multiply
                int p1 = i + j, p2 = i + j + 1;       // p2 = unit place, p1 = carry jabe ekhane
                int sum = mul + ans[p2];              // age theke jodi kichu thake shetar shathe add
                ans[p2] = sum % 10;                    // current position e ekta digit thakbe
                ans[p1] += sum / 10;                   // carry ta age er position e jog hobe
            }
        }

        string res;
        for (int num : ans)
        {
            if (!(res.empty() && num == 0))            // leading zero skip koro
            {
                res += to_string(num);
            }
        }
        return res;
    }
};