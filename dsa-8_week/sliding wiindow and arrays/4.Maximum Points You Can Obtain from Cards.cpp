// Time: O(k)  -> duita loop, protita k bar
// Space: O(1) -> shudhu kichu variable


/*
Input: cardPoints = [1, 2, 3, 4, 5, 6, 1], k = 3, n = 7
Step	Combination	    Card gulo	sum	    ans
0	    3 bam + 0 dan	1, 2, 3	    6	    6
1	    2 bam + 1 dan	1, 2, 1	    4	    6
2	    1 bam + 2 dan	1, 6, 1	    8	    8
3	    0 bam + 3 dan	5, 6, 1	    12	    12

Final answer = 12.  
*/
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int sum = 0, n = cardPoints.size();
        // prothom k ta card bam (shuru) theke nilam, eta i starting sum
        for (int i = 0; i < k; i++)
        {
            sum += cardPoints[i];
        }
        // ekhon porjonto eta i best answer (shob k ta bam theke)
        // NOTE: sum ber hoye jawar PORE ans = sum, age korle ans = 0 thake
        int ans = sum;
        // ekhon ek ek kore bam theke ekta chhere dan theke ekta nibo
        for (int i = 0; i < k; i++)
        {
            sum -= cardPoints[k - 1 - i];   // bam side er shesh card ta chharlam
            sum += cardPoints[n - 1 - i];   // dan side er shesh theke ekta card nilam
            // notun combination er sum ager best er cheye boro hole update
            ans = max(ans, sum);
        }
        return ans;
    }
};
