// O(n) (average),
// SC: O(n) (map e max n/2 + 1 ta alada number thake).

/*
nums = [4, 1, 2, 1, 2]

Map banar por: {4:1, 1:2, 2:2}

entry	p.second == 1?
4 : 1	✅ yes, return 4
1 : 2	skip
2 : 2	skip

*/

class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        unordered_map<int, int> freq; // key = number, value = oi number koyta bar ashe
        for (int x : nums)            // array er protita number dhoro
        {
            freq[x]++; // x er count 1 barao (notun hole 0 theke shuru hoy)
        }
        for (auto &p : freq) // map er protita (number, count) jora dekho
        {
            if (p.second == 1) // p.second = count. count 1 mane ekbar ashe
            {
                return p.first; // p.first = number, seta-i answer
            }
        }

        return 0; // kokhono cholbe na (single number guaranteed), shudhu compiler er jonno
    }
};

// OR

/*
Optimal, O(1) space (XOR)

Interviewer er follow-up chhilo: O(1) extra space. Er jonno ^ (XOR) lage. Eta ami dichhi, tai “nijey na kora”.

XOR er 3 ta rule:

a ^ a = 0 (same duita bhule jay)
a ^ 0 = a
Order mane na (a ^ b ^ a = b)


nums = [4, 1, 2, 1, 2]

x	result (por)
4	0 ^ 4 = 4
1	4 ^ 1 = 5
2	5 ^ 2 = 7
1	7 ^ 1 = 6
2	6 ^ 2 = 4

Return 4 ✅. Order alada hole-o same answer, karon 1^1 ar 2^2 shob jaygay cancel hoy.
*/

// TC: O(n), 
// SC: O(1).

class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int result = 0; // 0 diye shuru, karon a ^ 0 = a (kono khoti kore na)
        for (int x : nums) // protita number dhoro
        {                
            result ^= x; // result er sathe XOR. same jora hole 0 hoye jay
        }
        return result; // jora sob gayeb, shudhu single number baki
    }
};