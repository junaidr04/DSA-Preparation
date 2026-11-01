// TC: O(n). 3 ta alada pass, prottek ta O(n).
// SC: O(n). leftMax ar rightMax, duto extra array.

/*
Dry run [2, 0, 1, 3] (n = 4):

i	height	leftMax[i]	rightMax[i]	    min	    jol = min - height
0	2	    2	        3	            2	        0
1	0	    2	        3	            2	        2
2	1	    2	        3	            2	        1
3	3	    3	        3	            3	        0
leftMax build: [2, max(2,0)=2, max(2,1)=2, max(2,3)=3] = [2, 2, 2, 3]
rightMax build (ulte dik theke): rightMax[3]=3, rightMax[2]=max(3,1)=3, rightMax[1]=max(3,0)=3, rightMax[0]=max(3,2)=3 = [3, 3, 3, 3]
Total jol = 0 + 2 + 1 + 0 = 3 ✅
*/

class Solution
{
public:
    int trap(vector<int>& height)
    {
        int n = height.size();
        if (n == 0)
            return 0;                                   // edge: empty input

        vector<int> leftMax(n), rightMax(n);

        leftMax[0] = height[0];                         // prothom bar er left max nijei
        for (int i = 1; i < n; i++)                     // left theke dane jachi
        {
            leftMax[i] = max(leftMax[i - 1], height[i]); // ager max ar ekhon er bar, duto'r boro ta
        }

        rightMax[n - 1] = height[n - 1];                // shesh bar er right max nijei
        for (int i = n - 2; i >= 0; i--)                // FIX D: n-2 theke, karon n-1 age-i set kora (nahole rightMax[n] out of bounds)
        {
            rightMax[i] = max(rightMax[i + 1], height[i]); // FIX E: "ar" na, comma (,) diye argument alada
        }

        int water = 0;                                  // mot jol
        for (int i = 0; i < n; i++)
        {
            water += min(leftMax[i], rightMax[i]) - height[i]; // level = duto dik er chhoto, tar theke nijer height minus
        }
        return water;                                   // return loop er BAIRE
    }
};





// OR

// TC: O(n): prottek step e ekta pointer ek ghor sore, total n step.
// SC: O(1): shudhu kichu int variable.

/*
Dry run [3, 0, 2]

Shuru: l=0, r=2, leftMost=0, rightMost=0, ans=0

step	l	r	height[l]	height[r]	kon side	        ki hoy	                                    leftMost	rightMost	ans
1	    0	2	3	        2	        3<2 na, right	    rightMost(0) < 2, tai rightMost=2, r--	    0	        2	        0
2	    0	1	3	        0	        3<0 na, right	    rightMost(2) < 0? na, ans += 2-0 = 2, r--	0	        2	        2
	    0	0			                l<r false, thamo				

Output 2 ✅ (expected 2)

“Keno” er answer (tomar pending question)

*/

class Solution
{
public:
    int trap(vector<int>& height)
    {
        int l = 0, r = height.size() - 1;   // duto pointer, duto dik theke
        int ans = 0;                        // mot jol
        int leftMost = 0, rightMost = 0;    // ekhon porjonto left / right e dekha shobcheye boro bar

        while (l < r)                       // duto pointer meet korle thamo
        {
            if (height[l] < height[r])      // left bar chhoto, tai left er jol level = leftMost (right e oitar cheye boro ache)
            {
                if (leftMost < height[l])
                {
                    leftMost = height[l];           // FIX: leftMost ke update, height[l] na bodlano
                }
                else
                {
                    ans += leftMost - height[l];    // leftMost boro ba equal, tai jol joma
                }
                l++;                                // left pointer dane
            }
            else                            // right bar chhoto ba equal
            {
                if (rightMost < height[r])
                {
                    rightMost = height[r];          // FIX: rightMost ke update
                }
                else
                {
                    ans += rightMost - height[r];   // jol joma
                }
                r--;                                // right pointer bame
            }
        }
        return ans;                         // return loop er BAIRE
    }
};