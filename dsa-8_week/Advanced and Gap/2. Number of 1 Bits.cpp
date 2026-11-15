// TC: O(k), k = 1 bit er songkha (max 31, mane prai constant)
// SC: O(1); 


/*
n & (n-1) kaj kore? (interviewer er “keno”)

n - 1 korle duita jinis hoy:

n er sobcheye dan er 1 ta 0 hoye jay
oi 1 er dan er sob 0 gulo 1 hoye jay
n     = 1 0 1 1 0 0
n - 1 = 1 0 1 0 1 1
n&n-1 = 1 0 1 0 0 0


Dry run: n = 11 (1011)
iteration	n (binary)	n-1	    n & (n-1)	count
1	        1011	    1010	1010 (10)	1
2	        1010	    1001	1000 (8)	2
3	        1000	    0111	0000 (0)	3

n = 0, loop thame. Return 3  
*/
class Solution {
public:
    int hammingWeight(int n) {
        int count=0;          // koyta '1' pelam, ta gonar jonno, 0 theke shuru
        while(n)              // n != 0 porjonto cholbe. n 0 mane ar kono '1' bit baki nei
        {
            n=n&(n-1);        // n er sobcheye dan er '1' bit ta muche dilo (baki bit same)
            count++;          // ekta '1' muchlam, tai count 1 baralam
        }
        return count;         // loop shesh = sob '1' muchha shesh, count e total '1' er songkha
    }
};