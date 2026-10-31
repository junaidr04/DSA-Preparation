// TC: O(n). Prottek index ekbar push, ekbar pop.
// SC: O(n). Worst case increasing heights e stack e shob index.

/*
কয়েকটা দেয়াল পাশাপাশি দাঁড়িয়ে আছে। প্রত্যেকটার উচ্চতা আলাদা।
        6
      | |
    5 | |
    | | |
    | | |     3
2   | | |   |
|   | | |   |
--------------
2   1 5 6 2 3


আমাদের কাজ হলো এই দেয়ালগুলো ব্যবহার করে সবচেয়ে বড় আয়তাকার জায়গা (Rectangle) খুঁজে বের করা।

Rectangle-এর Area:

Area = Height × Width
Example
heights = {2, 1, 5, 6, 2, 3};


এখন 5 এবং 6 উচ্চতার দুইটা দেয়াল দেখো।

আমরা যদি 5 উচ্চতা নিয়ে Rectangle বানাই:

- Height = 5
- Width = 2
- Area = 5 × 2 = 10
এখন প্রশ্ন হলো, আমরা কীভাবে বুঝব Rectangle কতদূর পর্যন্ত বানাতে পারব?
১. দুই পাশের ছোট দেয়াল খুঁজব
ধরো, আমরা height 5 নিয়ে Rectangle বানাতে চাই।

তাহলে:
- বাম দিকে height 1 আছে। এটা 5-এর চেয়ে ছোট।
- ডান দিকে height 2 আছে। এটাও 5-এর চেয়ে ছোট।
এই দুইটা ছোট দেয়ালের মাঝখানেই আমরা height 5 দিয়ে Rectangle বানাতে পারব।

তাই:
Left = 1
Right = 4

Width = Right - Left - 1
      = 4 - 1 - 1
      = 2

Area = 5 × 2 = 10


২. Stack কেন লাগবে?
এখন প্রতিটা দেয়ালের জন্য বারবার বাম-ডান খুঁজলে সময় বেশি লাগবে।

তাই Stack ব্যবহার করব।

সহজ নিয়ম:
1. নতুন দেয়াল আগেরটার চেয়ে বড় হলে Stack-এ রাখব।
2. নতুন দেয়াল ছোট হলে Stack থেকে আগের বড় দেয়াল বের করব।
3. বের করার সময় তার Rectangle-এর Area হিসাব করব।
4. সবশেষে সবচেয়ে বড় Area রাখব।
৩. আরেকটা ছোট উদাহরণ
heights = {2, 4, 6, 2};


এখানে 6-এর পরে 2 এসেছে।

মানে 6-এর চেয়ে ছোট দেয়াল পাওয়া গেছে।

তাই 6 দিয়ে Rectangle হিসাব করব:
- Height = 6
- Width = 1
- Area = 6
এরপর 4 দিয়েও Rectangle হিসাব করব:
- Height = 4
- Width = 2
- Area = 8
এবার 2 দিয়ে পুরো চারটা দেয়াল নিয়ে Rectangle বানালে:
- Height = 2
- Width = 4
- Area = 8
সুতরাং Maximum Area = 8।


Example: [2, 1, 5, 6, 2, 3] (n = 6)

Shuru: st = [], best = 0

i	            curH	while shorto	       pop (h)	            left	    width = i-left-1	area	best	push er por stack
0	            2	    stack khali					                                                         0	        [0]
1	            1	    1 < 2 ✅	             idx 0 (h=2)	     -1 (khali)	    1-(-1)-1 = 1	    2	    2
                        stack khali,thamo					                                            	            [1]
2	            5	    5 < 1? ❌				                                                	        2	       [1, 2]
3	            6	    6 < 5? ❌					                                                        2	       [1, 2, 3]
4	            2	    2 < 6 ✅	             idx 3 (h=6)	    2	            4-2-1 = 1	        6	    6
                        2 < 5 ✅	            idx 2 (h=5)	        1	            4-1-1 = 2	        10	    10
                        2 < 1? ❌ thamo						                                                            [1, 4]
5	            3	    3 < 2? ❌					                                                        10	        [1, 4, 5]
6 (sentinel)	0	    0 < 3 ✅	            idx 5 (h=3)	        4	            6-4-1 = 1	        3	    10
                        0 < 2 ✅	            idx 4 (h=2)	        1	            6-1-1 = 4	        8	    10
                        0 < 1 ✅	            idx 1 (h=1)	        -1 (khali)	    6-(-1)-1 = 6	    6	    10
                        stack khali, thamo						                                                           [6]

Output: 10 ✅
*/

class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int n = heights.size();      // koyta bar ache
        stack<int> st;               // stack e INDEX rakhbo, ar stack er bhitore height increasing thakbe
        int ans = 0;                // ekhon porjonto paoa shobcheye boro area
        for (int i = 0; i <= n; i++) // i = n porjonto, shesh e ekta "kolpito" bar (sentinel) er jonno
        {
            int curH; // ekhon er bar er height
            if (i == n)
            {
                curH = 0; // sentinel: height 0, jate stack er shob bar pop hoy
            }
            else
            {
                curH = heights[i]; // normal bar: asol height
            }

            // curH jotokkhon top er height er cheye chhoto, top bar ta ar right e barte parbe na
            while (!st.empty() && curH < heights[st.top()])
            {
                int h = heights[st.top()]; // pop korar AGE height rekhe nilam (pore hariye jabe)
                st.pop();                  // oi bar ta ekhon "thamlo", tar area ber korbo

                int left; // left stopper: pop er POR stack er notun top
                if (st.empty())
                {
                    left = -1; // stack khali mane left e kono chhoto bar nai, tai -1
                }
                else
                {
                    left = st.top(); // left e prothom chhoto bar er index
                }
                int width = i - left - 1;    // right stopper = i, left stopper = left, duto-i range er BAIRE, tai -1
                ans = max(ans, h * width); // area = height * width, boro hole best update
            }
            st.push(i); // i ke stack e rakhlam (sentinel er index o push hoy, kintu tar por ar kichu ashe na)
        }
        return ans; // return loop er BAIRE
    }
};