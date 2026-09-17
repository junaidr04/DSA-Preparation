// Problem: Plus One
// Platform: NeetCode
// Link: https://neetcode.io/problems/plus-one
// time complexity: O(n); n = number of digits in the input array
// space complexity: O(1); only using a constant amount of extra space

/*
Example diye calculation (n = 129 → carry propagate case)

Input: digits = [1, 2, 9], n = 3

Loop iteration 1: i = 2

digits[2] = 9, check 9 < 9 → false
digits[2] = 0 → digits = [1, 2, 0]
Loop চলবে (return হয়নি)

Loop iteration 2: i = 1

digits[1] = 2, check 2 < 9 → true
digits[1]++ → 3 → digits = [1, 3, 0]
return digits → সাথে সাথে বেরিয়ে যাবে

Output: [1, 3, 0] ✅ (129 + 1 = 130 ✓)

All-9s case (n = 999) diye calculation

Input: digits = [9, 9, 9], n = 3

i=2: digits[2]=9, 9<9 false → digits[2]=0 → [9,9,0]
i=1: digits[1]=9, 9<9 false → digits[1]=0 → [9,0,0]
i=0: digits[0]=9, 9<9 false → digits[0]=0 → [0,0,0]
Loop শেষ (i=-1 হয়ে গেছে, condition i>=0 false)
digits.insert(digits.begin(), 1) → শুরুতে 1 বসে → [1, 0, 0, 0]

Output: [1, 0, 0, 0] ✅ (999 + 1 = 1000 ✓)  
*/

class Solution
{
public:
    vector<int> plusOne(vector<int>& digits)
    {
        int n = digits.size();
        for (int i = n - 1; i >= 0; i--)    // last index theke shuru, carry propagate korar jonno
        {
            if (digits[i] < 9)
            {
                digits[i]++;                  // simple, carry lagbe na, kaj shesh
                return digits;                // shathe shathe return kore dao
            }
            digits[i] = 0;                    // 9 chilo, tai 0 hoye carry পরের ঘরে jabe
        }
        // Ei point e ashe manei shob digit 9 chilo (jemon 999 -> 1000)
        digits.insert(digits.begin(), 1);    // shurute ekটা notun 1 boshao
        return digits;
    }
};