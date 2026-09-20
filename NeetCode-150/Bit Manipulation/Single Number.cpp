// Problem: Single Number
// Platform: NeetCode
// Link: https://neetcode.io/problems/single-number
// time complexity: O(n); Array e n ta element ache, loop ekbar matro shob element er upor diye chole, Protita element e ^= operation constant time (O(1)) e hoy
// space complexity: O(1); Khali ekta extra variable (ans) use hocche, array size er upor depend kore na Kono extra data structure (hashmap, array) lage nai

/*
Example diye Calculation

Input: [4, 1, 2, 1, 2]

Binary e convert kore dekhi (4 bit e dhorlam shohoj bujhar jonno):

4 = 0100
1 = 0001
2 = 0010
1 = 0001
2 = 0010

Step by step XOR calculation (ans = 0 diye shuru):

Step	ans (before)	num	    XOR calculation	    ans (after)
1	    0000	        4	    0000 ^ 0100	        0100
2	    0100	        1	    0100 ^ 0001	        0101
3	    0101	        2	    0101 ^ 0010	        0111
4	    0111	        1	    0111 ^ 0001	        0110
5	    0110	        2	    0110 ^ 0010	        0100

Final ans = 0100 = 4 ✅

Ki hoilo bujhi:

Step 2 → 4 (0100) XOR 1 (0001) = 0101 — dutar bit ekta jaygay match korlo na tai combine hoye gelo
Step 4 → age j 1 add hoisilo, oi 1 abar ashe, tai XOR kore oi bit ta abar 0 hoye gelo (cancel out)
Step 5 → same vabe 2 abar ashe, tar bit o cancel hoye jay
Reshe jay khali 4 — jeta duibar chilo na, ekbar matro chilo
*/

class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int ans = 0; // ans e 0 diye start, karon 0 XOR kono number = shei number
        for (int num : nums)
        {
            ans ^= num; // duplicate gulo nijeder shathe XOR hoye 0 hoye jabe, unique ta reshe jabe
        }
        return ans; // last e ans e shudhu unique number ta thakbe
    }
};