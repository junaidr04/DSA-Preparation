// Problem: Non-Cyclical Number
// Platform: NeetCode
// Link: https://neetcode.io/problems/non-cyclical-number
// time complexity: O(log n); n = input number.. er digit-sum calculation (কারণ digit সংখ্যা log₁₀(n)), ar overall কতবার loop চলবে সেটা bound করা কঠিন exactly, kintু practically cycle খুব দ্রুত (mostly 8-এ গিয়ে আটকায় বা 1-এ পৌঁছায়) — amortized O(log n) ধরা হয়।
// space complexity: O(log n); visited set e maximum যতগুলো unique number cycle detect হওয়ার আগে জমা হতে পারে, তার উপর নির্ভর করে (practically ছোট)। 


/*
n = 19 দিয়ে পুরো trace
Outer loop — Iteration 1: n = 19

Check: n != 1 (true, 19≠1) && !visited.count(19) (true, empty set) → loop চলবে

visited.insert(19) → visited = {19}
sum = 0

Inner loop (digit বের করে square করে যোগ করা):

n (before)	digit = n%10	digit²	sum += digit²	    n = n/10 (after)
19	        9	            81	    sum = 0+81 = 81	    n = 19/10 = 1
1	        1	            1	    sum = 81+1 = 82	    n = 1/10 = 0

Inner loop condition n > 0 → 0 > 0 false → inner loop exit

n = sum = 82

Outer loop — Iteration 2: n = 82

Check: n != 1 (true) && !visited.count(82) (true) → loop চলবে

visited.insert(82) → visited = {19, 82}
sum = 0

Inner loop:

n (before)	digit	digit²	sum	                n (after)
82	        2	    4	    sum = 0+4 = 4	    n = 82/10 = 8
8	        8	    64	    sum = 4+64 = 68	    n = 8/10 = 0

Inner loop exit (n=0)

n = sum = 68

Outer loop — Iteration 3: n = 68

Check: n != 1 (true) && !visited.count(68) (true) → loop চলবে

visited.insert(68) → visited = {19, 82, 68}
sum = 0

Inner loop:

n (before)	digit	digit²	sum	                n (after)
68	        8	    64	    sum = 0+64 = 64	    n = 68/10 = 6
6	        6	    36	    sum = 64+36 = 100	n = 6/10 = 0

Inner loop exit

n = sum = 100
Outer loop — Iteration 4: n = 100
Check: n != 1 (true) && !visited.count(100) (true) → loop চলবে
visited.insert(100) → visited = {19, 82, 68, 100}
sum = 0

Inner loop:

n (before)	digit	digit²	sum	                n (after)
100	        0	    0	    sum = 0+0 = 0	    n = 100/10 = 10
10	        0	    0	    sum = 0+0 = 0	    n = 10/10 = 1
1	        1	    1	    sum = 0+1 = 1	    n = 1/10 = 0

Inner loop exit (n=0)

n = sum = 1
Outer loop — Check আবার: n = 1
Check: n != 1 → 1 != 1 → false → outer loop exit
Return
return n == 1 → 1 == 1 → true
তাই isHappy(19) → true ✅

*/
class Solution
{
public:
    bool isHappy(int n)
    {
        unordered_set<int> visited;              // ekhon obdi dekha shob number rakhbe (cycle detect korte)
        while (n != 1 && !visited.count(n))      // n=1 hole happy, na hole cycle e porcho kina check
        {
            visited.insert(n);                    // current n ke visited mark koro
            int sum = 0;
            while (n > 0)
            {
                int digit = n % 10;                // last digit ber koro
                sum += digit * digit;              // digit square kore sum e jog koro
                n /= 10;                            // last digit remove koro (n ke choto koro)
            }
            n = sum;                                // notun n hobe digit-squares er sum
        }
        return n == 1;                             // n==1 hole true, cycle e atke gele false
    }
};