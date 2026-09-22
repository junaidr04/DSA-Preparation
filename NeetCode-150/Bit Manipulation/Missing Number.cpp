// Problem: Missing Number
// Platform: NeetCode
// Link: https://neetcode.io/problems/missing-number
// time complexity: O(n); where n is the length of the input array
// space complexity: O(1); Khali ans ar n variable use hocche, extra space lagena (input array chara)

/*
Input: nums = [3, 0, 1] → n = 3

ans shuru: ans = n = 3

i	ans(before)	i	        nums[i]	    ans ^ i ^ nums[i]	    ans (after)
0	3 (011)	    0 (000) 	3 (011) 	011 ^ 000 ^ 011 = 000	0
1	0 (000)	    1 (001) 	0 (000) 	000 ^ 001 ^ 000 = 001	1
2	1 (001)	    2 (010) 	1 (001) 	001 ^ 010 ^ 001 = 010	2

Final ans = 010 = 2 ✅

Ki hoilo bujhi:

Amra 0,1,2,3 (n=3 diye shuru kora, tai 0 theke 3) ar array [3,0,1] — shob mile XOR korlam
3 array e ache, index e-o 3 (ans er shuru te) ashlo — pair hoye cancel
0 array e ache, loop e index 0-o ashlo — pair hoye cancel
1 array e ache, loop e index 1-o ashlo — pair hoye cancel
2 kothao pair hoy nai (array e nai, kintu 0-3 range e thakar kotha chilo) — tai eita reshe gelo  
*/

class Solution
{
public:
    int missingNumber(vector<int>& nums)
    {
        int n = nums.size();   // array er length
        int ans = n;           // n ke shuru teই XOR chain e add kore dilam (karon index e n ashbe na loop e)
        for (int i = 0; i < n; i++)
        {
            ans = ans ^ i ^ nums[i]; // index ar value duitai XOR kortesi — pair hoye gele cancel hobe
        }
        return ans; // jeita pair hoy nai (missing number) sheita reshe jabe
    }
};