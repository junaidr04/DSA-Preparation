// Problem: Valid Parenthesis String
// Platform: NeetCode
// Link: https://neetcode.io/problems/valid-parenthesis-string
// time complexity: O(n) - String-ta ekbar traverse kora hoy
// space complexity: O(1) - Shudhu duita variable use hocche

/*
Tomake ekta string s deya thakbe, jekhane shudhu tinta character thakte pare: '(', ')', ar '*'.
'*' ekta wildcard — eta tin vabe treat kora jay:
Ekta '(' hishebe
Ekta ')' hishebe
Ekta empty string (mane kichu na, ignore kore dao) hishebe
Tomake bolte hobe — '*' gulo-ke এমনভাবে assign kora jay kina (kono ekta combination diye) je, resulting string-ta valid parenthesis string hoye jay.
Valid parenthesis mane: protita '('-er ekta matching ')' thakte hobe pore, ar kono point-e closing bracket-er shonkha opening bracket-er shonkha ke exceed korte parbe na.

Example 1:

s = "()"
Simple valid parenthesis, kono * nai.
Answer = true

Example 2:

s = "(*)"
* ke empty hishebe treat korle: "()" — valid!
Answer = true

Example 3:

s = "(*))"
* ke '(' hishebe treat korle: "(())" — valid!
Answer = true

Example 4:

s = "(((*"
3 ta ( ar 1 ta *. *-ke ) hishebe treat korleo "((()" moto kichu hoy — kintu tao 2 ta ( unmatched thake.
Kono combination-e valid banano jabe na.
Answer = false

Key point bujhar jonno:

Brute force e protita * er jonno 3 ta choice try korle — exponential hoye jabe (3^n), onek slow.
Greedy trick: * er exact value fix na kore, amra "koto range-er moddhe open bracket count thakte pare" eta track korbo.

Input:

s = "(*))"

Initial:
minOpen = 0, maxOpen = 0

Loop (protita character process kori):

i	c	minOpen (before op)	    maxOpen (before op) 	Operation	    minOpen (after)	    maxOpen (after)	    maxOpen<0?	    minOpen<0? (clip)
0	(	    0	                0	                    min++, max++	    1	                1	                No	            No
1	*	    1	                1	                    min--, max++	    0	                2	                No	            No
2	)	    0	                2	                    min--, max--	    -1	                1	                No	            Ha → minOpen=0
3	)	    0	                1	                    min--, max--	    -1	                0	                No	            Ha → minOpen=0

Loop shesh:

minOpen = 0, maxOpen = 0

Final check: minOpen == 0 → true ✓

Ki holo bujhi:

i=0 ((): Both bound barhe — minOpen=1, maxOpen=1. Ekhon porjonto guaranteed 1 ta open bracket ache.
i=1 (*): * ke worst case () dhore) minOpen kome 0 hoy, best case (( dhore) maxOpen barhe 2 hoy. Mane ekhon "possible open bracket count" 0 theke 2-er moddhe je kono ekta hote pare — eta e range tracking-er মূল idea.
i=2 ()): Duitai kome — minOpen=-1 (invalid lower bound, clip kore 0 kora holo), maxOpen=1. Ekhon range 0 theke 1।
i=3 ()): Abar duitai kome — minOpen=-1→clip 0, maxOpen=0। Range ekhon 0 theke 0 — mane exactly 0 open bracket thakte hobe, r kono flexibility nai।
Loop shesh e minOpen=0 — mane emon kমপক্ষে ekta valid assignment ache jekhane shob bracket match hoy। Tai true।
*/

class Solution
{
public:
    // এই function check করবে string valid parenthesis string কি না
    bool checkValidString(string s)
    {
        // minOpen = এখন পর্যন্ত minimum কতগুলো unmatched '(' থাকতে পারে
        // maxOpen = এখন পর্যন্ত maximum কতগুলো unmatched '(' থাকতে পারে
        int maxOpen = 0, minOpen = 0;
        // string s-এর প্রতিটা character এক এক করে c-তে আসবে
        for (char c : s)
        {
            // যদি current character '(' হয়
            if (c == '(')
            {
                // '(' অবশ্যই একটি নতুন open bracket যোগ করে
                // তাই minimum possible open bracket ১ বাড়বে
                minOpen++;

                // maximum possible open bracket-ও ১ বাড়বে
                maxOpen++;
            }

            // যদি current character ')' হয়
            else if (c == ')')
            {
                // ')' একটি open bracket বন্ধ করে দেয়
                // তাই minimum possible open bracket ১ কমবে
                minOpen--;

                // maximum possible open bracket-ও ১ কমবে
                maxOpen--;
            }

            // যদি current character '*' হয়
            else
            {
                // minimum open bracket বের করার জন্য
                // '*' কে ')' হিসেবে ধরা হচ্ছে
                // তাই open bracket ১ কমছে
                minOpen--;

                // maximum open bracket বের করার জন্য
                // '*' কে '(' হিসেবে ধরা হচ্ছে
                // তাই open bracket ১ বাড়ছে
                maxOpen++;
            }
            // যদি maxOpen negative হয়ে যায়
            // তাহলে maximum possible '(' দিয়েও current ')' কে match করা সম্ভব না
            // অর্থাৎ ')' বেশি হয়ে গেছে
            // তাই string কখনো valid হতে পারবে না
            if (maxOpen < 0)
                return false;

            // unmatched open bracket-এর সংখ্যা negative হতে পারে না
            // তাই minOpen negative হলে সেটাকে 0 করে দিচ্ছি
            if (minOpen < 0)
                minOpen = 0;
        }
        // loop শেষ হওয়ার পরে যদি minimum possible unmatched '(' = 0 হয়
        // তাহলে অন্তত একটি way আছে যেখানে সব bracket perfectly match করা সম্ভব
        // তাই string valid
        return (minOpen == 0);
    }
};