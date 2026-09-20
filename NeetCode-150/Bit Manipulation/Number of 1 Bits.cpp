// Problem: Number of 1 Bits
// Platform: NeetCode
// Link: https://neetcode.io/problems/number-of-1-bits
// time complexity: O(k); jekhane k = number of set bits in n; loop cholbe protibar ekta set bit remove korar jonno, tai loop cholbe shudhu set bits er shongkha onujayi
// space complexity: O(1); Only a constant amount of extra space is used

/*
Example diye Calculation

Input: n = 11

11 → binary: 1011
Step	n (before)	    n-1	        n & (n-1)	                count
1	    1011 (11)	    1010 (10)	1011 & 1010 = 1010 (10)	    1
2	    1010 (10)	    1001 (9)	1010 & 1001 = 1000 (8)	    2
3	    1000 (8)	    0111 (7)	1000 & 0111 = 0000 (0)	    3

n = 0, loop shesh → count = 3 ✅

(11 = 1011, ekhane sotti 3 ta '1' bit ache — 1,0,1,1 er modde 3 ta 1)
*/

class Solution
{
public:
    int hammingWeight(uint32_t n)
    {
        int count = 0; // koyta set bit ache tar count rakhbo
        while (n)
        {
            n = n & (n - 1); // rightmost set bit ke 0 kore dey
            count++;         // protibar ekta set bit remove hoile count barai
        }
        return count; // shesh e total set bit shongkha
    }
};