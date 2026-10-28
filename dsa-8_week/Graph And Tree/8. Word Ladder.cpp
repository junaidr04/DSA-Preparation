// Time: O(N · L² · 26), mane O(N · L²). Prottek shobdo ekbar-i queue te dhoke (erase er karone). Prottek shobdo er jonno L position × 26 okkhor = 26L ta temp banano hoy. Prottek temp er copy, hash ar lookup e O(L) lage. Tai N × 26L × L.
// Space: O(N · L). Set e max N ta shobdo, queue e max N ta shobdo, prottek ta L length er.


class Solution
{
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        // wordList ke set e rakhlam: O(1) lookup, ar set theke muchle "visited" hishebe kaj kore
        unordered_set<string> Word(wordList.begin(), wordList.end());
        // endWord talika te na thakle kono path-i possible na, tai shorashori 0
        if (!Word.count(endWord))
            return 0;
        // queue e {shobdo, ekhon porjonto koyta shobdo path e} rakhbo (BFS = level by level)
        queue<pair<string, int>> q;
        q.push({beginWord, 1}); // shuru te nijei path e, tai length = 1
        while (!q.empty())
        {
            // shamner shobdo ar tar length ber kore pop korlam
            auto [word, length] = q.front();
            q.pop();
            // BFS e prothom bar endWord pele sheta-i shobcheye chhoto path
            if (word == endWord)
                return length;
            // prottek position e ghurbo
            for (int i = 0; i < word.size(); i++)
            {
                // oi position e 'a' theke 'z' boshabo
                for (char c = 'a'; c <= 'z'; c++)
                {
                    // word ke bodlabo na, copy (temp) bodlabo
                    string temp = word;
                    temp[i] = c;
                    // temp jodi set e thake, mane valid ar ekhono dekha hoy ni
                    if (Word.count(temp))
                    {
                        q.push({temp, length + 1}); // ek dhap beshi
                        Word.erase(temp);           // muche dilam = visited mark, jate abar na dhuke
                    }
                }
            }
        }
        // queue shesh, endWord e pouchano gelo na
        return 0;
    }
};