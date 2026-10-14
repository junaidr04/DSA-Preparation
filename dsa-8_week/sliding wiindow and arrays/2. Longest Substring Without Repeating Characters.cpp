// Time complexity: O(n)  -> l ar r dutoi max n bar kore move kore
// Space complexity: O(min(n, m))  -> m = character set er size (ASCII hole 128/256)

/*
Start: st = {}, l = 0, ans = 0

r	s[r]	Duplicate?	    While er bhitore	                Insert er por st	Window [l, r]	len	ans
0	a	        na	        -	                                {a}	                [0,0]	        1	1
1	b	        na	        -	                                {a,b}	            [0,1]	        2	2
2	c	        na	        -	                                {a,b,c}	            [0,2]	        3	3
3	a	        ha	        erase s[0]=a, l=1	                {b,c,a}	            [1,3]	        3	3
4	b	        ha	        erase s[1]=b, l=2	                {c,a,b}	            [2,4]	        3	3
5	c	        ha	        erase s[2]=c, l=3	                {a,b,c}	            [3,5]	        3	3
6	b	        ha	        erase s[3]=a, l=4. 
                            Tao b ache, tai erase s[4]=b, l=5	{c,b}	            [5,6]	        2	3
7	b	        ha	        erase s[5]=c, l=6. 
                            Tao b ache, tai erase s[6]=b, l=7	{b}	                [7,7]	        1	3

Final answer = 3 (“abc”).
*/


class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // st = current window [l, r] er moddhe thaka character gulo
        unordered_set<char> st;
        int l = 0;      // window er bam dik
        int ans = 0;    // ekhon porjonto shobcheye boro valid window er length
        // r = window er dan dik, protibar ek ghor agay
        for (int r = 0; r < s.size(); r++)
        {
            // s[r] jodi window e already thake, mane duplicate
            // tahole bam dik theke ek ek kore character fele dao,
            // jotokkhon na s[r] er duplicate ta ber hoye jay
            while (st.count(s[r]))
            {
                st.erase(s[l]);  // NOTE: s[l] erase hobe, s[r] na (bam dik er character jay)
                l++;             // window er bam dik ek ghor agao
            }
            st.insert(s[r]); // ekhon window te duplicate nei, tai s[r] dhukao
            ans = max(ans, r - l + 1); // window valid, tai ekhon length check kore ans update
        }
        return ans;
    }
};
