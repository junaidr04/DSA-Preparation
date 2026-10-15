// Time: O(n + m)  -> l ar r dutoi max n bar kore move kore, freq banate O(m)
// Space: O(min(m, charset))


/*
freq[c] > 0 → ei character ta ekhono dorkar
freq[c] == 0 → ekdom thik ache
freq[c] < 0 → extra ache
need = koyta real character ekhono baki. need == 0 hole window valid.

Input: s = "ADOBECODEBANC", t = "ABC"

index: 0 1 2 3 4 5 6 7 8 9 10 11 12
char:  A D O B E C O D E B A  N  C

Start: freq = {A:1, B:1, C:1}, need = 3, l = 0, minLen = ∞

Part 1: r agay, window boro hocche
r	s[r]	freq e ki holo	Real requirement puron?	    need	Window valid?
0	A	    A: 1→0	        ha (0 >= 0)	                2	        na
1	D	    D: 0→-1	        na (extra)	                2	        na
2	O	    O: 0→-1	        na	                        2	        na
3	B	    B: 1→0	        ha	                        1	        na
4	E	    E: 0→-1	        na	                        1	        na
5	C	    C: 1→0	        ha	                        0	        ha!

Part 2: r = 5 e window valid, ekhon l diye choto kori
Step	Window [l, r]	    Length	Kaj	            s[l] ber korle	need	Result
1	    [0,5] “ADOBEC”	    6	    minLen = 6, 
                                    start = 0	    A: 0→1 (> 0)	1	    l = 1, window ar valid na, while shesh

Part 3: r abar agay (r = 6 theke 9)
r	s[r]	freq	    need	Kaj
6	O	    O: -1→-2	1	    extra character, need bodlay na
7	D	    D: -1→-2	1	    extra
8	E	    E: -1→-2	1	    extra
9	B	    B: 0→-1	    1	    extra B, karon B er requirement age e puron

Part 4: r = 10, A ashe, abar valid

freq[A]: 0→0 hoy (age 1 chilo, ber hoye 1 hoye gechilo, ekhon abar 0), >= 0 tai need = 0.

Step	Window [l, r]	    Length	minLen update?	s[l] ber korle	    need	Result
1	    [1,10]	            10	    na (10 > 6)	    D: -2→-1	        0	    still valid, continue
2	    [2,10]	            9	    na	            O: -2→-1	        0	    still valid
3	    [3,10]	            8	    na	            B: -1→0	            0	    still valid (B extra chilo)
4	    [4,10]	            7	    na	            E: -2→-1	        0	    still valid
5	    [5,10] “CODEBA”	    6	    na (6 = 6)	    C: 0→1 (> 0)	    1	    l = 6, valid na, shesh

Part 5: r = 11, 12
r	s[r]	need	Kaj
11	N	    1	    N t te nei, extra
12	C	    0	    C: 1→0, valid!

Step	Window [l, r]	    Length	minLen update?	        s[l] ber korle	need	Result
1	    [6,12]	            7	    na	                    O: -1→0	        0	    valid
2	    [7,12]	            6	    na (6 = 6)	            D: -1→0	        0	    valid
3	    [8,12] “DEBANC”	    5	    minLen = 5, start = 8	E: -1→0	        0	    valid
4	    [9,12] “BANC”	    4	    minLen = 4, start = 9	B: 0→1 (> 0)	1	    l = 10, valid na, shesh
Final

minLen = 4, start = 9, tai s.substr(9, 4) = “BANC”  
*/
class Solution {
public:
    string minWindow(string s, string t) {
        // s ba t empty hole answer nai
        if (s.empty() || t.empty())
            return "";
        // freq[c] = t te c er koyta dorkar (positive = ekhono baki, 0 = ekdom thik, negative = extra ache)
        unordered_map<char, int> freq;
        for (char c : t)
        {
            freq[c]++;
        }
        int l = 0;              // window er bam dik
        int need = t.size();    // koyta character ekhono baki (duplicate soho gona)
        int start = 0;          // best window er shuru
        int minLen = INT_MAX;   // best window er length (INT_MAX = ekhono kono window pai nai)
        // r = window er dan dik, protibar ek ghor agay
        for (int r = 0; r < s.size(); r++)
        {
            freq[s[r]]--;           // s[r] window e dhukalo
            // freq >= 0 mane ei character ta t er ekta REAL requirement puron korlo
            // (negative hole extra character, need komano jabe na)
            if (freq[s[r]] >= 0)
            {
                need--;
            }
            // need == 0 mane window valid, ekhon bam dik theke choto korar chesta
            while (need == 0)
            {
                // notun window ager cheye choto hole answer update
                if (r - l + 1 < minLen)
                {
                    minLen = r - l + 1;
                    start = l;
                }
                freq[s[l]]++;       // s[l] window theke ber korlam
                // freq > 0 mane ekta REAL requirement bhenge gelo, window ar valid na
                // (<= 0 hole extra character chilo, window ekhono valid thakbe)
                if (freq[s[l]] > 0)
                {
                    need++;
                }
                l++;                // bam dik ek ghor agao
            }
        }
        // minLen update na hole kono valid window pai nai
        if (minLen == INT_MAX)
            return "";
        else
            return s.substr(start, minLen);
    }
};