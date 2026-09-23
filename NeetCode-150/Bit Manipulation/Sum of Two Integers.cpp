// Problem: Sum of Two Integers
// Platform: NeetCode
// Link: https://neetcode.io/problems/sum-of-two-integers
// time complexity: O(1); Worst case loop 32 bar (bit size) porjonto cholte pare, karon protibar carry ekta kore bit shift hoye "eshore" jay, ar 32-bit integer e max 32 bar carry propagate hote pare Fixed upper bound bole eita constant time dhora hoy
// space complexity: O(1); Khali carry variable use hocche, extra space lagena

/*
Input: a = 5, b = 3

5 = 101
3 = 011
Step	a (before)	b (before)	carry = a & b	        a = a ^ b	            b = carry << 1
1	    101(5)	    011(3)	    101 & 011 = 001 (1)	    101 ^ 011 = 110 (6)	    001 << 1 = 010 (2)
2	    110 (6)	    010 (2)	    110 & 010 = 010 (2)	    110 ^ 010 = 100 (4)	    010 << 1 = 100 (4)
3	    100 (4)	    100 (4)	    100 & 100 = 100 (4)	    100 ^ 100 = 000 (0)	    100 << 1 = 1000 (8)
4	    000 (0)	    1000 (8)	000 & 1000 = 0	        000 ^ 1000 = 1000 (8)	0 << 1 = 0

b = 0 hoye gelo, loop shesh → a = 1000 = 8 ✅ (5+3=8, thik ache)

Ki hocche bujhi:

a ^ b protibar step e "carry chara" sum dey — jekhane bit different sheikhane 1 boshe
a & b protibar step e dekhay kon position e carry generate hobe (dutai 1 thakle)
carry << 1 diye carry ta next (upor) position e niye jaoya hoy, karon addition e carry always next bit e jay
Eita repeat hote thake jotokkhon na notun kono carry na bere (b=0)  
*/

class Solution
{
public:
    int getSum(int a, int b)
    {
        while (b != 0) // jotokkhon carry (b) ache, add korte thakbo
        {
            int carry = a & b;   // kon position e carry hobe seita ber kortesi
            a = a ^ b;            // carry chara sum ber kortesi
            b = carry << 1;       // carry ta next position e shift kore dilam, next iteration e add hobe
        }
        return a; // shesh e b=0 hoye gele, a-tei final sum thake
    }
};