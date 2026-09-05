// Problem: Jump Game
// Platform: NeetCode
// Link: https://neetcode.io/problems/jump-game
// time complexity: O(n) - Array-ta ekbar matro traverse kora hoy
// space complexity: O(1) - Shudhu ekta variable (far) use hocche

/*
je index aa jabe shee index er porjonto koto dur jaoya jay (i + nums[i]) sheta check kora hoyeche.
Input:

cpp
nums = [2, 3, 1, 1, 4]

Initial:

far = 0

Loop shuru (i = 0 theke i = 4 porjonto):

i	nums[i] 	Check: i > far? 	i + nums[i]	    far = max(far, i+nums[i])
0	2	        0 > 0? No	        0+2 = 2	            max(0, 2) = 2
1	3	        1 > 2? No	        1+3 = 4	            max(2, 4) = 4
2	1	        2 > 4? No	        2+1 = 3	            max(4, 3) = 4
3	1	        3 > 4? No	        3+1 = 4	            max(4, 4) = 4
4	4	        4 > 4? No	        4+4 = 8	            max(4, 8) = 8

Loop shesh — return true
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        // far = ekhon porjonto shobcheye dur kon index e pouchano jay (farthest reachable)
        int far = 0;
        for (int i = 0; i < nums.size(); i++) {
            // jodi current index (i) already "far" er baire hoye jay,
            // mane ei index e pouchanoi possible na — tai false return
            if (i > far)
                return false;
            
            // ei index theke koto dur jaoya jay (i + nums[i]) shetar shathe
            // ekhon porjonto best "far" compare kore boro-ta rakho
            far = max(far, i + nums[i]);
        }
        // loop shesh mane shob index e pouchano gese, tai true
        return true;
    }
};