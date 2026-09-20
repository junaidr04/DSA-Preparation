// Problem: Counting Bits
// Platform: NeetCode
// Link: https://neetcode.io/problems/counting-bits
// time complexity: O(n log n); jekhane n = number of bits in the input; loop cholbe protibar ekta bit check korar jonno, tai loop cholbe shudhu set bits er shongkha onujayi
// space complexity: O(n); ekta extra array (ans) use hocche, jekhane n = number of bits in the input

/*
Example diye Calculation

Input: n = 5

i	num shuru	Brian Kernighan steps	            count	ans[i]
0	0	        loop e dhoke nai (num=0)	        0	    0
1	1 (001)	    1 & 0 = 0 → 1 step	                1	    1
2	2 (010)	    2 & 1 = 0 → 1 step	                1	    1
3	3 (011)	    3 & 2 = 010, 2 & 1 = 0 → 2 step	    2	    2
4	4 (100)	    4 & 3 = 0 → 1 step	                1	    1
5	5 (101)	    5 & 4 = 100, 4 & 3 = 0 → 2 step	    2	    2

Output: [0, 1, 1, 2, 1, 2]
*/

class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> ans(n + 1, 0); // 0 theke n porjonto answer rakhar jonno vector
        for (int i = 0; i <= n; i++) 
        {
            int count = 0; // protita i er jonno fresh count shuru
            int num = i;   // i ke temp variable e copy kortesi, jate i nosto na hoy
            while (num) 
            {
                num = num & (num - 1); // rightmost set bit remove kore
                count++;               // protibar ekta set bit count hoy
            }
            ans[i] = count; // i er total set bit count array e rakhi
        }
        return ans;
    }
};