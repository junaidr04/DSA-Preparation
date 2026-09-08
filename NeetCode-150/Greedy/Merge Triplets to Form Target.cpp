// Problem: Merge Triplets to Form Target
// Platform: NeetCode
// Link: https://neetcode.io/problems/merge-triplets-to-form-target
// time complexity: O(n) - We iterate through the triplets once
// space complexity: O(1) - Using constant extra space

/*
Tomake ekta 2D array triplets deya thakbe, jekhane protita triplet [x, y, z] format-e ache (tinta number). Ar ekta target triplet deya thakbe [x, y, z] format-e.
Merge operation ki: Duita triplet-ke merge korle, protita position-e maximum value nao. Jemon [2,5,3] ar [1,7,5] merge korle hoy [max(2,1), max(5,7), max(3,5)] = [2,7,5].
Tomake bolte hobe — triplets array theke je kono kotogulo triplet bebohar kore (ekbar kore, order jekono) — proti bar merge kore — target-er shathe exactly match kora jay kina.

Example 1:

triplets = [[2,5,3],[1,8,4],[1,7,5]]
target = [2,7,5]
[2,5,3] ar [1,7,5] merge koro: [max(2,1), max(5,7), max(3,5)] = [2,7,5]
Eta e exactly target!
Answer = true

Example 2:

triplets = [[3,4,5],[4,5,6]]
target = [3,2,5]
[3,4,5] ar [4,5,6] — dutar 2nd position-e (index 1) value 4 ba 5, kintu target-e chai 2.
Merge korle 2nd position-e kokhono 2 pawa jabe na (karon merge always max nay, r 4,5 dutai 2-er cheye boro — max hole 2 asheee na, r kono triplet e use korleo 2nd position-e value 2-er cheye choto hote hobe na tar mane sheta already target exceed kore fele).
Answer = false
triplets = [[2,5,3],[1,8,4],[1,7,5]]
target = [2,7,5]

Initial:

best0 = 0, best1 = 0, best2 = 0

Loop (protita triplet check kori):

Triplet	    Check: t[0]≤2? t[1]≤7? t[2]≤5?	 Valid?	     Action
[2,5,3]	    2≤2 ✓, 5≤7 ✓, 3≤5 ✓	            Valid	    best0=max(0,2)=2, best1=max(0,5)=5, best2=max(0,3)=3
[1,8,4]	    1≤2 ✓, 8≤7? NO	                Invalid	    Skip — best0,1,2 unchanged
[1,7,5]	    1≤2 ✓, 7≤7 ✓, 5≤5 ✓	            Valid	    best0=max(2,1)=2, best1=max(5,7)=7, best2=max(3,5)=5

Loop shesh:

best0=2, best1=7, best2=5
target = [2,7,5]

Final check: best0==2 ✓, best1==7 ✓, best2==5 ✓ → return true ✓
*/

class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        // best0, best1, best2 = valid triplet-gulor moddhe protita position-e
        // ekhon porjonto shobcheye boro value ja target exceed kore na
        int best0 = 0, best1 = 0, best2 = 0;
        for (auto& t : triplets) 
        {
            // ei triplet "valid" kina check koro — kono position-e target
            // exceed korle, ei triplet kokhono use kora jabe na (skip)
            if (t[0] <= target[0] && t[1] <= target[1] && t[2] <= target[2]) 
            {
                // valid hole, protita position-e best value update koro
                best0 = max(best0, t[0]);
                best1 = max(best1, t[1]);
                best2 = max(best2, t[2]);
            }
        }
        // valid triplet-gulo merge kore proti position-e exactly target
        // pawa gelo kina check koro
        if (best0 == target[0] && best1 == target[1] && best2 == target[2]) 
        {
            return true;
        }
        return false;
    }
};
