// Problem: Jump Game II
// Platform: NeetCode
// Link: https://neetcode.io/problems/jump-game-ii
// time complexity: O(n) - Array-ta ekbar matro traverse kora hoy
// space complexity: O(1) - Shudhu ekta variable (jumps) use hocche

/*
Jump Game I-er moto e array nums deya thakbe, jekhane nums[i] bolche index i theke maximum koto dur jump kora jay. Ei baar tomake guaranteed je last index e pouchano jabei (Jump Game I-er moto "possible kina" check korte hobe na).
Tomake bolte hobe — last index e pouchate minimum koyta jump lagbe.

*/

class Solution {
public:
    int jump(vector<int>& nums) {
        // far = ekhon porjonto shobcheye dur kon index e pouchano jay (farthest reachable)
        // jump = koyta jump loga hoyeche ekhon porjonto
        // currEnd = current jump-er "range" kothay shesh hocche
        int far = 0, jump = 0, currEnd = 0;
        
        // last index porjonto jaoar dorkar nai loop e — karon last index e pouchale
        // ar notun jump nebar dorkar nai, tai nums.size()-1 porjonto loop
        for (int i = 0; i < nums.size() - 1; i++) 
        {
            // ei index theke koto dur jaoya jay, tar shathe best "far" compare kore rakho
            far = max(far, i + nums[i]);
            // jodi current jump-er range-er "shesh" e pouche jai (i == currEnd),
            // mane ei range-e ar egono jabe na, tai notun jump nite hobe
            if (i == currEnd) 
            {
                jump++;              // ekta notun jump nilam
                currEnd = far;       // notun jump-er range set holo
            }
        }
        
        return jump;
    }
};