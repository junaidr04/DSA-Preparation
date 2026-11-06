// Time: O(log n). Protyek iteration e left ba right move kore range ordhek hoye jay. n theke 1 e jete log₂ n bar lage. (n = 7 hole max prai 3 iteration, dry run 1 e 3 bar-i holo.)
// Space: O(1). Shudhu left, right, mid variable, kono extra array/recursion nei.


/*
nums = [4, 5, 6, 7, 0, 1, 2], target = 0

Index: 0 1 2 3 4 5 6

Iter	left	right	mid	    nums[mid]	Kon tukro sorted?	        Target range e?	         Ki hoy
1	    0	    6	    3	    7	        4 <= 7 → left [4,5,6,7]	    4 <= 0? Na	            left = 4
2	    4	    6	    5	    1	        0 <= 1 → left [0,1]	        0 <= 0 && 0 < 1 Hya	    right = 4
3	    4	    4	    4	    0	        nums[mid] == target		                            return 4 ✅

Bujhar tip: Iter 1 e 0 ta left tukro (4..7) er baire, tai left = mid + 1 kore right tukro te gelam. Ei bhabe protyek bar ordhek array fele dei.  
*/

class Solution
{
public:
    int search(vector<int>& nums, int target)
    {
        // left = shuru index, right = shesh index (pura array niye shuru)
        int left = 0, right = nums.size() - 1;
        // jotokkhon kompokkhe ekta element baki ache, totokkhon chalbo
        // (<= dewa hoyeche, karon left == right hole o ekta element baki)
        while(left <= right)
        {
            // majhkhaner index (overflow bachate left + ...)
            int mid = left + (right - left) / 2;
            // mid e-i target pele, oi index return
            if(nums[mid] == target)
                return mid;
            // left tukro [left..mid] sorted kina check
            if(nums[left] <= nums[mid])
            {
                // target ki left tukro er range er bhitore? (nums[left] <= target < nums[mid])
                if(nums[left] <= target && target < nums[mid])
                {
                    // hya, target left e, tai right ke mid er baam e soraI
                    right = mid - 1;
                }
                else
                {
                    // na, target left e nei, tai right tukro te jai
                    left = mid + 1;
                }
            }
            // noile right tukro [mid..right] sorted
            else
            {
                // target ki right tukro er range er bhitore? (nums[mid] < target <= nums[right])
                if(nums[right] >= target && target > nums[mid])
                {
                    // hya, target right e, tai left ke mid er dan e soraI
                    left = mid + 1;
                }
                else
                {
                    // na, target right e nei, tai left tukro te jai
                    right = mid - 1;
                }
            }
        }
        // loop shesh, target pai ni
        return -1;
    }
};