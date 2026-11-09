// Time: O(L) each, L = word/prefix er length. Word er songkha N er upor depend kore na (brute force e O(N·L) chhilo).
// Space: worst case O(N·L) (kono prefix share na hole). Prottek node e 26 pointer, tai node-protti memory ektu beshi.


class TrieNode
{
public:
    TrieNode* children[26];   // 26 ta pointer, index 0='a', 1='b' ... 25='z'. children[i] mane "i-th akkhor diye ekta child ache kina"
    bool isEnd;               // true mane ei node e ekta word shesh hoyeche (search ar startsWith er pharak ei-ta)

    TrieNode()
    {
        isEnd = false;                    // notun node e kono word shesh hoyni
        for (int i = 0; i < 26; i++)      // 26 ta child er jonno loop
        {
            children[i] = NULL;           // shuru te kono child nai. (FIX: ager bar ekhane ':' chhilo, ekhon ';')
        }
    }
};

class Trie
{
public:
    TrieNode* root;                       // root e kono akkhor thake na, shob word ekhan theke shuru

    Trie()
    {
        root = new TrieNode();            // khali ekta root toiri
    }

    void insert(string word)
    {
        TrieNode* cur = root;             // shobar age root theke shuru
        for (char ch : word)              // word er prottek akkhor niye ek ek kore
        {
            int idx = ch - 'a';           // 'a'->0, 'b'->1 ... (FIX: ager bar 'c' chhilo, variable er naam 'ch')
            if (cur->children[idx] == NULL)       // ei akkhor er child ekhono nai?
            {
                cur->children[idx] = new TrieNode();   // tahole notun node banao
            }
            cur = cur->children[idx];     // child e egiye jao (age thaka hok ba notun, dui khetrei)
        }

        cur->isEnd = true;                // puro word ses, ei node e word shesh hoyeche bole mark koro
    }

    bool search(string word)
    {
        TrieNode* cur = root;             // root theke shuru
        for (char ch : word)              // prottek akkhor dhore egao
        {
            int idx = ch - 'a';           // akkhor theke index 
            if (cur->children[idx] == NULL)       // path majhe bhenge gelo?
            {
                return false;             // tahole ei word kokhono insert hoyni
            }
            cur = cur->children[idx];     // path ache, egiye jao
        }
        return cur->isEnd;                // path pelei hobe na, ekhane word shesh hoyechilo kina seta dekho
    }

    bool startsWith(string prefix)
    {
        TrieNode* cur = root;             // root theke shuru
        for (char ch : prefix)            // prefix er prottek akkhor
        {
            int idx = ch - 'a';           // akkhor theke index 
            if (cur->children[idx] == NULL)       // path bhenge gele
            {
                return false;             // kono word ei prefix diye shuru hoyni
            }
            cur = cur->children[idx];     // egiye jao
        }
        return true;                      // path pawa gelei prefix ache, isEnd dekhar dorkar nai
    }
};