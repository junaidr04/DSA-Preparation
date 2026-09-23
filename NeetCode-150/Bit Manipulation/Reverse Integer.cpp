// Problem: Reverse Integer
// Platform: NeetCode
// Link: https://neetcode.io/problems/reverse-integer
// time complexity: O(log x); x er koyta digit ache, loop totobar cholbe.. Number of digits e ekta number x er, seita hocche log10(x) — tai time complexity O(log x)
// space complexity: O(1); Khali ans ar digit variable use hocche, extra space lagena

/*
Input: x = 123

Step	x (before)	digit = x%10	x = x/10	overflow check	        ans = ans*10+digit
1	    123	        3	            12	        pass (0 shoto choto)	0*10+3 = 3
2	    12	        2	            1	        pass	                3*10+2 = 32
3	    1	        1	            0	        pass	                32*10+1 = 321

x = 0 hoye loop shesh → ans = 321 ✅

Overflow example (x = 1534236469):

Ei number reverse korle hoy 9646324351, jeta INT_MAX (2147483647) theke onek boro — 32-bit e dhorbe na.

Loop cholte cholte jokhon ans prai 214748364 (INT_MAX/10) er kache pouche jabe, ar porer digit boro hobe, tokhon condition ans == INT_MAX/10 && digit > 7 (ba ans > INT_MAX/10) true hoye return 0 kore dibe — overflow howar age e catch kore fela hoy।

*/

class Solution
{
public:
    int reverse(int x)
    {
        int ans = 0;
        while (x) // jotokkhon x e digit ache
        {
            int digit = x % 10; // last digit ber kortesi (negative x hole digit-o negative hobe)
            x = x / 10;          // last digit remove kortesi x theke
            // positive overflow check — ans*10+digit korle INT_MAX cross korbe kina
            if (ans > INT_MAX/10 || (ans == INT_MAX/10 && digit > 7))
            {
                return 0;
            }
            // negative overflow check — ans*10+digit korle INT_MIN theke choto hoye jabe kina
            if (ans < INT_MIN/10 || (ans == INT_MIN/10 && digit < -8))
            {
                return 0;
            }
            ans = ans*10 + digit; // digit ta ans er shathe jog kortesi (reverse howar jonno)
        }
        return ans; // shesh e reverse howa number
    }
};