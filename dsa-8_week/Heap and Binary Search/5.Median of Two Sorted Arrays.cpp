// Time: O(log(min(m, n))), protyek iteration e chhoto array-r search range ordhek hoy. Eta O(log(m + n)) er cheye bhalo.
// Space: O(1).


/*
Dry run (nums1 = [1, 3, 8], nums2 = [2, 4, 6, 9], m = 3, n = 4, half = 4):

Iter	left	right	i	j	L1	R1	L2	R2	Check	                Ki hoy
1	    0	    3	    1	3	1	3	6	9	1 <= 9 ✅, 6 <= 3 ❌	L2 > R1, left = 2
2	    2	    3	    2	2	3	8	4	6	3 <= 6 ✅, 4 <= 8 ✅	valid!

Total 7 bijor, tai max(L1, L2) = max(3, 4) = 4 → return 4.0 ✅  
*/

class Solution
{
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        int m = nums1.size(), n = nums2.size();
        // nums1 sobshomoy chhoto array hobe, noile j negative hote pare
        if(m > n)
            return findMedianSortedArrays(nums2, nums1);

        // left half e koyta element lagbe (bijor hole left e ekta beshi)
        int half = (m + n + 1) / 2;

        // i = nums1 theke koyta element left e nibo (0 theke m porjonto)
        int left = 0, right = m;

        // left == right hole o ekta candidate i baki thake, tai <=
        while(left <= right)
        {
            // i = nums1 theke koyta left e, j = nums2 theke baki koyta
            int i = left + (right - left) / 2;
            int j = half - i;

            // L1: nums1 er left er shesh element (kichu na thakle -infinity)
            int L1;
            if(i == 0)
                L1 = INT_MIN;
            else
                L1 = nums1[i - 1];

            // R1: nums1 er right er prothom element (kichu na thakle +infinity)
            int R1;
            if(i == m)
                R1 = INT_MAX;
            else
                R1 = nums1[i];

            // L2: nums2 er left er shesh element
            int L2;
            if(j == 0)
                L2 = INT_MIN;
            else
                L2 = nums2[j - 1];

            // R2: nums2 er right er prothom element
            int R2;
            if(j == n)
                R2 = INT_MAX;
            else
                R2 = nums2[j];

            // valid kata: left er shob element right er shob element theke choto/shoman
            if(L1 <= R2 && L2 <= R1)
            {
                // GAP A: total bijor hole median = left er sobcheye boro
                if((m + n) % 2 == 1)
                {
                    return (double)max(L1, L2);
                }

                // GAP B: total zor hole median = (left er boro + right er choto) / 2.0
                return (max(L1, L2) + min(R1, R2)) / 2.0;
            }
            // GAP C: L1 > R2 mane nums1 theke beshi element nisi, i ke baame soraai
            else if(L1 > R2)
            {
                right = i - 1;
            }
            // GAP D: noile L2 > R1, nums1 theke aro element lagbe, i ke dane soraai
            else
            {
                left = i + 1;
            }
        }

        // shob input valid hole ekhane kokhono ashbe na
        return 0.0;
    }
};