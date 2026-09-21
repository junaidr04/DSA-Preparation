// Problem: Reverse Bits
// Platform: NeetCode
// Link: https://neetcode.io/problems/reverse-bits
// time complexity: O(n); jekhane n = number of bits in the input; loop cholbe protibar ekta bit check korar jonno, tai loop cholbe shudhu set bits er shongkha onujayi
// space complexity: O(1); 

/*
Input: n = 11 — 4 bit e dhori shohoj bujhar jonno (n = 1011)

Full 32 bit e leading zero gulo dhorlam, kintu shudhu last 4 bit e focus kori (baki shob 0, tai unchanged thakbe):

n = ...0000 1011
i	bit = (n>>i)&1	bit==1?	    position (31-i)	    ans e ki set hoy
0	1	            ✅	        31	                ans e position 31 set
1	1	            ✅	        30	                ans e position 30 set
2	0	            ❌	        29	                kichu hoy na
3	1	            ✅	        28	                ans e position 28 set

Result (last 4 bit reverse howar por):

Original last 4 bit: 1011
Reverse:              1101

Position 31, 30, 28 e 1 set hoise, position 29 e 0 — mane reverse howar por ans er top 4 bit hocche 1101 — ✅ thik ache (1011 reverse = 1101)  
*/

class Solution
{
public:
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t ans = 0; // result rakhar jonno, shuru te shob bit 0
        for (int i = 0; i < 32; i++)
        {
            int bit = (n >> i) & 1; // n er i-th position er bit ta ber kortesi
            if (bit == 1)
            {
                ans = ans | (1u << (31 - i)); // jodi bit 1 hoy, reverse position (31-i) e 1 bosai
            }
        }
        return ans; // shob bit reverse hoye result e thake
    }
};