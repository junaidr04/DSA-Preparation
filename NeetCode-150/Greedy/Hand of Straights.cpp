// Problem: Hand of Straights
// Platform: NeetCode
// Link: https://neetcode.io/problems/hand-of-straights
// time complexity: O(n log n) - Sorting the hand takes O(n log n) time
// space complexity: O(n) - Using a hash map to store the frequency of each card

/*
Tomake ekta array hand deya thakbe — protita card-er value bojhaay. Ar ekta integer groupSize deya thakbe.
Tomake bolte hobe — ei card gulo ke groupSize-ta kore consecutive (lagatar) value-er group-e bhag kora jay kina. Jodi jay, true return korba, naile false.
Consecutive mane: protita group-er moddhe values gulo ekdom pashapashi hote hobe (gap thakle hobe na) — jemon [3,4,5] ekta valid group (groupSize=3), kintu [3,4,6] na (gap ache 5 nai).
Example 1:

hand = [1, 2, 3, 6, 2, 3, 4, 7, 8]
groupSize = 3
Ei card gulo ke 3 ta group-e bhag korte hobe, protita group-e 3 ta consecutive value:
Group 1: [1, 2, 3]
Group 2: [2, 3, 4]
Group 3: [6, 7, 8]
Shob card use hoye geche, protita group consecutive — Answer = true

Input:
hand = [1, 2, 3, 6, 2, 3, 4, 7, 8]
groupSize = 3

Step 1: Divisibility check

hand.size() = 9, groupSize = 3
9 % 3 = 0 → OK, continue

Step 2: Frequency map banano

freq = {1:1, 2:2, 3:2, 4:1, 6:1, 7:1, 8:1}

Step 3: Sort kora

sorted hand = [1, 2, 2, 3, 3, 4, 6, 7, 8]

Step 4: Outer loop (i = 0 theke 8):

i	hand[i]	 freq[hand[i]]	 Action
0	 1	        1 (≠0)	     Notun group shuru — nested loop chalao

Nested loop (i=0, hand[i]=1, group range = 1,2,3):

j	freq[j] before	 Check	    freq[j] after
1	1	              ≠0, OK	1-1=0
2	2	              ≠0, OK	2-1=1
3	2	              ≠0, OK	2-1=1

Group [1,2,3] complete! freq ekhon: {1:0, 2:1, 3:1, 4:1, 6:1, 7:1, 8:1}

Outer loop continue:

i	hand[i]	  freq[hand[i]]	   Action
1	2	       1 (≠0)	       Notun group shuru — nested loop chalao

Nested loop (i=1, hand[i]=2, group range = 2,3,4):

j	freq[j] before	 Check	    freq[j] after
2	1	             ≠0, OK	        1-1=0
3	1	             ≠0, OK	        1-1=0
4	1	             ≠0, OK	        1-1=0

Group [2,3,4] complete! freq ekhon: {1:0, 2:0, 3:0, 4:0, 6:1, 7:1, 8:1}

Outer loop continue:

i	hand[i]	  freq[hand[i]]	    Action
2	2	        freq[2]=0	    Skip (continue) — already use hoye geche
3	3	        freq[3]=0	    Skip (continue)
4	3	        freq[3]=0	    Skip (continue)
5	4	        freq[4]=0	    Skip (continue)
6	6	        freq[6]=1 (≠0)	Notun group shuru

Nested loop (i=6, hand[i]=6, group range = 6,7,8):

j	freq[j] before	   Check	   freq[j] after
6	1	                ≠0, OK	        0
7	1	                ≠0, OK	        0
8	1	                ≠0, OK	        0

Group [6,7,8] complete! freq ekhon shob 0.

Outer loop continue:

i	hand[i]	 freq[hand[i]]	 Action
7	7	          0	        Skip
8	8	          0	        Skip

Loop shesh — kono false return hoyni, tai return true
*/

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        // total card shonkha groupSize diye evenly bhag na hole, possible na
        if (hand.size() % groupSize != 0) 
        {
            return false;
        }
        // proti value koybar ache, seta count kori
        unordered_map<int, int> freq;
        for (int num : hand) 
        {
            freq[num]++;
        }
        
        // smallest value theke process korar jonno sort kori
        sort(hand.begin(), hand.end());
        for (int i = 0; i < hand.size(); i++) 
        {
            // jodi ei value already onno group-e use hoye geche (freq 0),
            // tahole notun kore group shuru korar dorkar nai, skip koro
            if (freq[hand[i]] == 0)
                continue;
            // freq[hand[i]] > 0 mane ei value diye notun group shuru kora jay
            // (jehetu sorted, hand[i] ei ekhon porjonto shobcheye choto available value)
            // hand[i] theke hand[i]+groupSize-1 porjonto proti consecutive value lagbe
            for (int j = hand[i]; j < hand[i] + groupSize; j++) 
            {
                // consecutive value ta available na thakle, group banano jacche na
                if (freq[j] == 0)
                    return false;
                // available thakle, use kore freq kome dao
                freq[j]--;
            }
        }
        return true;
    }
};