// Time: O(n)  -> l ar r dutoi bhitore ashe, total max n step
// Space: O(1) -> shudhu kichu variable

/*
Dry run: height = [1,8,6,2,5,4,8,3,7]

index:  0  1  2  3  4  5  6  7  8
value:  1  8  6  2  5  4  8  3  7

Step	l	r	height[l]	height[r]	width	minH	water	ans	    Kon pointer sorlo
1	    0	8	1	        7	        8	    1	    8	    8	    l++ (1 < 7)
2	    1	8	8	        7	        7	    7	    49	    49	    r-- (8 >= 7)
3	    1	7	8	        3	        6	    3	    18	    49	    r--
4	    1	6	8	        8	        5	    8	    40	    49	    r-- (equal, else)
5	    1	5	8	        4	        4	    4	    16	    49	    r--
6	    1	4	8	        5	        3	    5	    15	    49	    r--
7	    1	3	8	        2	        2	    2	    4	    49	    r--
8	    1	2	8	        6	        1	    6	    6	    49	    r--  
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        // l = bam dik er line, r = dan dik er line
        // shuru te width shobcheye boro (duto prante)
        int l = 0, r = height.size() - 1, ans = 0;
        while (l < r)
        {
            // width = duita line er moddhe doori
            int width = r - l;
            // container er height nirdharon kore CHOTO line ta (pani uporei chole jabe)
            int heights = min(height[l], height[r]);
            // ei duita line diye koto pani rakha jay
            int water = heights * width;
            // ager best er cheye beshi hole update
            ans = max(ans, water);
            // choto line ta ke shorabo, karon:
            // boro line ta sorale width kome, height choto line er cheye beshi hobe na,
            // tai area kokhono barbe na. Choto line ta sorale-i barar chance ache.
            if (height[l] < height[r])
            {
                l++;    // bam er line choto, tai bam dik bhitore agao
            }
            else
            {
                r--;    // dan er line choto ba soman, tai dan dik bhitore agao
            }
        }
        return ans;
    }
};
