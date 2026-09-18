// Problem: Pow(x, n)
// Platform: NeetCode
// Link: https://neetcode.io/problems/powx-n
// time complexity: O(log n); প্রতি iteration এ N half হচ্ছে, তাই মোট iteration সংখ্যা log₂(n)।
// space complexity: O(1); 

/*
Example diye calculation (x = 2.0, n = 10)

N = 10 (positive, তাই negative-handling skip)। Binary e 10 = 1010।

Iteration	N (before)	N%2	        ans (multiply?)	    x (before square)	ans (after)	    x (after square)	N (after /2)
1	        10	        0 (even)	multiply হবে না	    2.0	                1.0	            4.0	                5
2	        5	        1 (odd)	    ans *= 4.0	        4.0	                4.0	            16.0	            2
3	        2	        0 (even)	multiply হবে না	    16.0	            4.0	            256.0	            1
4	        1	        1 (odd)	    ans *= 256.0	    256.0	            1024.0	        65536.0	            0

Loop condition N > 0 → 0 > 0 false → loop exit

Return ans = 1024.0 ✅ (2^10 = 1024 ✓)  
*/

class Solution
{
public:
    double myPow(double x, int n)
    {
        long long N = n;             // int overflow theke bachar jonno long long e convert
        if (N < 0)                   // negative exponent hole reciprocal niye positive banao
        {
            x = 1 / x;
            N = -N;
        }
        double ans = 1.0;
        while (N > 0)
        {
            if (N % 2 == 1)           // exponent odd hole, current x ta result e multiply koro
            {
                ans *= x;
            }
            x *= x;                    // x ke square koro (এইটাই "divide by 2" er সমতুল্য)
            N /= 2;                     // exponent ke half kore felo
        }
        return ans;
    }
};