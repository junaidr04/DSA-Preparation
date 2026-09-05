// Problem: Maximum Subarray
// Platform: NeetCode
// Link: https://neetcode.io/problems/maximum-subarray/question
// time complexity: O(n) - single pass through the array
// space complexity: O(1) - only a few variables used

/*
Input:

cpp
nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]

Initial:

currSum = nums[0] = -2
maxSum  = nums[0] = -2

Loop shuru (i = 1 theke i = 8 porjonto):

i	nums[i]	 currSum + nums[i]	currSum = max(nums[i], currSum+nums[i]) 	maxSum = max(maxSum, currSum)
1	  1	     -2+1 = -1	            max(1, -1) = 1	                             max(-2, 1) = 1
2	 -3	      1+(-3) = -2	        max(-3, -2) = -2	                        max(1, -2) = 1
3	 4	     -2+4 = 2	            max(4, 2) = 4	                            max(1, 4) = 4
4	 -1	     4+(-1) = 3	            max(-1, 3) = 3	                            max(4, 3) = 4
5	 2	     3+2 = 5	            max(2, 5) = 5	                            max(4, 5) = 5
6	 1	     5+1 = 6	            max(1, 6) = 6	                            max(5, 6) = 6
7	 -5	     6+(-5) = 1	            max(-5, 1) = 1	                            max(6, 1) = 6
8	 4	     1+4 = 5	            max(4, 5) = 5	                            max(6, 5) = 6

Loop shesh — return maxSum = 6
*/

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        // currSum = ekhon porjonto "best running" subarray er sum (jeta continue kora hocche)
        // maxSum = overall best ja ekhon porjonto pawa gese, eta answer track kore
        int currSum = nums[0], maxSum = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            // greedy decision: current element take purano subarray er shathe jog korbo,
            // naki eikhan theke notun subarray shuru korbo?
            // jodi currSum negative hoye jay (ba nums[i] tar theke boro hoy),
            // tahole purano ta felay dile better — karon negative sum jog korle
            // future sum ta shudhu kome jabe, tai fresh shuru kora lav
            currSum = max(nums[i], currSum + nums[i]);
            // proti step e overall maximum update kori
            maxSum = max(maxSum, currSum);
        }
        return maxSum;
    }
};