// Problem: Partition Labels
// Platform: NeetCode
// Link: https://neetcode.io/problems/partition-labels/question
// time complexity: O(n) - String-ta duibar traverse kora hoy (last occurrence banate, ar partition banate) — dutai linear, tai total O(n)
// space complexity: O(1) - Hashmap-e maximum 26 ta lowercase letter thakte pare (fixed), tai constant space

/*
Tomake ekta string s deya thakbe (shudhu lowercase letters). Tomake string-ta je koyta possible ততগুলো অংশে (partition) bhag korte hobe emon vabe je:
Protita letter shudhu ekta e partition-e dekha jabe (mane ekta letter jei partition-e ache, oi letter-er shob occurrence oi e partition-e thakte hobe — kono letter duita partition-e split hote parbe na).
Tumi maximum shonkha partition banate chao (mane jotoটা choto choto part-e bhaga jay, ততটাই bhalo).
Return korte hobe — protita partition-er length (size) ekta list/array hishebe.

Example 1:

s = "ababcbacadefegdehijhklij"

Partition hobe:

"ababcbaca" | "defegde" | "hijhklij"
Length: [9, 7, 8]

Kyano ei vabe bhaga holo:

a prothom dekha jay index 0-e, ar last dekha jay index 8-e. Tai a shoho jekono partition-e jodi a thake, oi partition kmpokkhe index 8 porjonto extend korte hobe.
b first dekha jay index 1-e, last index 5-e — eta o age-r partition-er moddhe pore jay (0-8 range-e).
c first index 4, last index 7 — eta o range-er moddhe.
Tai prothom partition 0 theke 8 (length 9) — কারণ ei range-er moddhekar shob letter-er "last occurrence" 8-er baire jay na।
Similarly porer part-gulo.  

Input:

cpp
s = "ababcbacadefegdehijhklij"

Step 1: Last occurrence map banano

Index diye dekhi:

Index: 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23
Char:  a  b  a  b  c  b  a  c  a  d  e  f  e  g  d  e  h  i  j  h  k  l  i  j

last map (protita character-er shesh dekha jaoya index):

last[a]=8, last[b]=5, last[c]=7, last[d]=14, last[e]=15, last[f]=11, 
last[g]=13, last[h]=19, last[i]=22, last[j]=23, last[k]=20, last[l]=21

Step 2: Main loop (start=0, end=0):

i	 s[i]	 last[s[i]]	  end=max(end,last[s[i]])	 i==end?	    Action
0	  a	        8	        max(0,8)=8	               No	        —
1	  b	        5	        max(8,5)=8	               No	        —
2	  a	        8	        max(8,8)=8	               No	        —
3	  b	        5	        max(8,5)=8	               No	        —
4	  c	        7	        max(8,7)=8	               No	        —
5	  b     	5	        max(8,5)=8	               No	        —
6	  a	        8	        max(8,8)=8	               No	        —
7	  c	        7	        max(8,7)=8	                No	        —
8	  a	        8	        max(8,8)=8	            Yes (8==8)	    ans.push(8-0+1=9), start=9
9	  d	        14	        max(8,14)=14	            No	        —
10	  e	        15	        max(14,15)=15	            No	        —
11	  f	        11	        max(15,11)=15	            No	        —
12	  e	        15	        max(15,15)=15	            No	—
13	  g	        13	        max(15,13)=15	            No	—
14	  d	        14	        max(15,14)=15	            No	—
15	  e	        15	        max(15,15)=15	         Yes (15==15)	ans.push(15-9+1=7), start=16
16	  h	        19	        max(15,19)=19	            No	—
17	  i	        22	        max(19,22)=22	            No	—
18	  j	        23	        max(22,23)=23	            No	—
19	  h	        19	        max(23,19)=23	            No	—
20	  k	        20	        max(23,20)=23	            No	—
21	  l	        21	        max(23,21)=23	            No	—
22	  i	        22	        max(23,22)=23	            No	—
23	  j	        23	        max(23,23)=23	        Yes (23==23)	ans.push(23-16+1=8), start=24

Loop shesh — ans = [9, 7, 8] ✓

Ki holo bujhi:

i=0 theke i=8: a first dekha jay index 0-e, last[a]=8 — tai end shuru theke 8-e set hoye jay. Ei majhkhane b ar c o ashe, kintu tader last occurrence (b→5, c→7) already 8-er moddhei pore jay, tai end r barhe na. Jokhon i=8-e pouchai, i==end (8==8) — mane ei point porjonto j character-gulo dekha geche, tader kono ta ar shamne kothao dekha jabe na — tai partition close kora jay. Length = 8-0+1 = 9.
i=9 theke i=15: Notun partition shuru — d(last=14), e(last=15) — end barhte barhte 15-e pouchay. i=15-e i==end, partition close. Length = 15-9+1 = 7.
i=16 theke i=23: Shesh partition — h,i,j,k,l shob mile end=23 porjonto extend hoy. i=23-e close. Length = 23-16+1 = 8.

Final answer: [9, 7, 8] — exactly problem statement-er example-er shathe match kore!
*/

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int n = s.size();
        vector<int> ans;
        int start = 0, end = 0;
        // protita character-er "last occurrence" index store kori
        unordered_map<char, int> last;
        for (int i = 0; i < n; i++) 
        {
            last[s[i]] = i;
        }
        for (int i = 0; i < n; i++) 
        {
            // current character-er last occurrence dekhe 'end' extend koro
            // (current partition-take kotodur porjonto jete hobe, seta update hocche)
            end = max(end, last[s[i]]);
            // jodi current index e 'end'-e pouche jai, mane ei partition-e
            // ja ja character ache, tader shob-er last occurrence cross hoye geche
            // — tai ei partition ekhane "close" kora jay
            if (i == end) 
            {
                ans.push_back(end - start + 1);  // partition-er length
                start = i + 1;  // notun partition porer index theke shuru
            }
        }
        return ans;
    }
};