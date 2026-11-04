// Time: O(n log n + n * L^2) average (unordered_map hash O(L), candidate banano O(L), L ta candidate, n ta word). n = 1000, L = 16 e khub choto.
// Space: O(n * L) map er jonno.

/*
Dry run (words = ["bdca", "a", "bda", "ba"]):

Sort er por: ["a", "ba", "bda", "bdca"]
"a": candidate "" dp te nei, best = 1, dp["a"] = 1, ans = 1
"ba": candidate "a" (dp = 1) → best = 2; "b" nei. dp["ba"] = 2, ans = 2
"bda": candidate "da" nei, "ba" (dp = 2) → best = 3, "bd" nei. dp["bda"] = 3, ans = 3
"bdca": candidate "dca", "bca" nei, "bda" (dp = 3) → best = 4, "bdc" nei. dp["bdca"] = 4, ans = 4
Return 4

*/

class Solution
{
public:
    // length diye sort er jonno comparator: choto length age
    static bool cmp(const string &a, const string &b)
    {
        // strict '<' (<= na), choto length age ashbe
        return a.size() < b.size();
    }

    int longestStrChain(vector<string> &words)
    {
        // choto length age, tai predecessor shobshomoy age-i dekha hobe
        sort(words.begin(), words.end(), cmp);

        // dp[w] = w te shesh hoy emon sobcheye boro chain er length
        unordered_map<string, int> dp;
        // shob dp er max, ei-i final answer
        int ans = 0;

        // sorted order e protyek word dekhi
        for (const string &w : words)
        {
            // base case: kono predecessor na thakle chain = 1 (shudhu nijei)
            // (position loop er BAIRE, noile protyek i te reset hoye jabe)
            int best = 1;

            // w theke protyek position er character ekta kore ber kori
            for (int i = 0; i < (int)w.size(); i++)
            {
                // i-th character bade candidate: age er ongsho + pore er ongsho
                string candidate = w.substr(0, i) + w.substr(i + 1);

                // candidate age dekha hoyeche (dp te ache) kina
                // (count age check, noile dp[candidate] e notun 0 entry toiri hoto)
                if (dp.count(candidate))
                {
                    // candidate er chain + 1 (w jog hole)
                    best = max(best, dp[candidate] + 1);
                }
            }

            // GAP 6: shob position dekha shesh, w er best ta dp te rakhi
            dp[w] = best;
            // shob word er moddhe sobcheye boro ta ans e rakhi
            ans = max(ans, best);
        }
        return ans;
    }
};