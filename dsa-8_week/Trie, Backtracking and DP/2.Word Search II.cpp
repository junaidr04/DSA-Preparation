// TC: O(N·L + m·n·4·3^(L-1)).. N·L: sob word Trie te dhukate. Prottek cell theke DFS L er beshi gobhir hoy na. Prothom dhape 4 dik, tarpor ager cell bad diye max 3 dik, tai 4·3^(L-1). Grid er DFS cost N er upor depend kore na. Brute force e prottek word er jonno alada DFS hoto, tai N·m·n·4·3^(L-1) hoto. Ei jaygay Trie ta benefit dey.
// SC: O(N·L) Trie er jonno. Grid er jonno extra space O(L) recursion stack er jonno.

/*
Dry run

Grid:

      c0 c1 c2 c3
r0:   o  a  a  n
r1:   e  t  a  e
r2:   i  h  k  r
r3:   i  f  l  v

words = ["oath", "pea", "eat", "rain"]

Trie (4 ta word insert hoyar por):

root
 |-- o -- a -- t -- h   (word = "oath")
 |-- p -- e -- a        (word = "pea")
 |-- e -- a -- t        (word = "eat")
 |-- r -- a -- i -- n   (word = "rain")

Start (0,0) = 'o':

root e o ache, tai node = o. Word khali, push na. (0,0) ke '#' kori.
Up: grid er baire, return. Down (1,0)='e': o er child shudhu a, e na, tai return. Left: baire. Right (0,1)='a': o er child a ache, egiye jai, '#' mark.
(0,1) theke Down (1,1)='t': oa er child t ache, egiye jai, '#' mark.
(1,1) theke Down (2,1)='h': oat er child h ache. node->word = "oath", tai result = [“oath”], word ke "" kori. '#' mark.
h theke 4 dik: (1,1) '#' (visited), (3,1)='f', (2,0)='i', (2,2)='k'. h er kono child nai, tai sob dike return.
Backtrack: (2,1) ke 'h' ferot dei. (1,1) er Left (1,0)='e' ar Right (1,2)='a' e oat er child nai, return. (1,1) ke 't' ferot dei.
(0,1) er Right (0,2)='a': oa er child shudhu t, tai return. (0,1) ferot dei, tarpor (0,0) ke 'o' ferot dei.

Baki cell gulo:

(0,1), (0,2), (0,3): 'a', 'a', 'n' diye kono word shuru hoy na (root e child nai), shathe shathe return.
(1,0)='e': root e e ache, kintu e er child shudhu a. Pashe o, i, t, kono a nai, dead end.
(1,3)='e': node = e, tarpor Left (1,2)='a' e ea, tarpor Left (1,1)='t' e eat. node->word = "eat", tai result = [“oath”, “eat”].
(2,3)='r': r er child shudhu a. Pashe e, v, k, kono a nai, dead end.
p grid e nai, tai "pea" kokhono pawa jay na. "rain" o na.

Final: ["oath", "eat"]  
*/
class TrieNode
{
public:
    TrieNode* children[26];   // 26 ta pointer. index 0='a' ... 25='z'. children[i] != NULL mane "i-th akkhor diye ekta path ache"
    string word;              // ei node e jodi kono word shesh hoy, oi puro word ta. na hole "" (khali)
    TrieNode()
    {
        for(int i = 0; i < 26; i++)       // 26 ta child er jonno loop
        {
            children[i] = NULL;           // notun node e shuru te kono child nai
        }
        // word string, tai default e khali thake, alada likhte hobe na
    }
};

class Solution
{
public:
    TrieNode* root = new TrieNode();      // Trie er root. root e kono akkhor thake na, sob word ekhan theke shuru
    // Ekta word ke Trie te dhukano
    void insertWord(string word)
    {
        TrieNode* curr = root;                    // sobar age root theke shuru
        for(char ch : word)                       // word er prottek akkhor niye ek ek kore
        {
            int idx = ch - 'a';                   // 'a'->0, 'b'->1 ... akkhor ke index e convert
            if(curr->children[idx] == NULL)       // ei akkhor er child ekhono nai?
            {
                curr->children[idx] = new TrieNode();   // tahole notun node banao
            }
            curr = curr->children[idx];           // child e egiye jao (age thaka hok ba notun, duto-i khetre)
        }
        curr->word = word;                        // shesh node e puro word ta rakho. eta isEnd er kaj + "kon word" er kaj, duto-i kore
    }

    // (r,c) cell theke DFS, node = Trie er ekhon kon jaygay achi
    void dfs(vector<vector<char>>& board, int r, int c, TrieNode* node, vector<string>& result)
    {
        // GAP 1: grid er baire gele thamo
        if(r < 0 || r >= board.size() || c < 0 || c >= board[0].size())
        {
            return;                               // r,c er 4 ta shorto: upore/niche/bame/dane baire. ei check age, noile board[r][c] e crash korbe
        }
        char ch = board[r][c];                    // ei cell er akkhor ta save rakho, karon pore '#' diye mark korbo ar backtrack e ferot dibo
        // GAP 2: duto jaygay thamo
        if(ch == '#' || node->children[ch - 'a'] == NULL)
        {
            return;                               // (a) '#' mane ei path e ei cell already use hoyeche (visited)
                                                  // (b) Trie te ei akkhor er child nai, mane kono word ei path e nai, tai aro khujle lav nai (early stop)
                                                  // '#' age check korte hobe, noile '#' - 'a' e kharap index hoye jabe
        }
        node = node->children[ch - 'a'];          // Trie te ekdhap egiye jao (grid er cell er sathe sathe)
        // GAP 3: word pawa gele result e rakho
        if(node->word != "")                      // khali na mane ei node e ekta word shesh hoyeche
        {
            result.push_back(node->word);         // word ta result e jog koro
            node->word = "";                      // khali kore dao, noile onno path diye abar ei node e ashle duplicate jabe
        }
        board[r][c] = '#';                        // GAP 4: cell ta visited mark. ei DFS e ar kew ei cell use korte parbe na
        dfs(board, r - 1, c, node, result);       // GAP 5: Up (upore)
        dfs(board, r + 1, c, node, result);       // Down (niche)
        dfs(board, r, c - 1, node, result);       // Left (bame)
        dfs(board, r, c + 1, node, result);       // Right (dane)
        board[r][c] = ch;                         // GAP 6: backtrack. cell ta ferot dao, noile onno path ba onno starting cell er DFS e ei cell ta "visited" thakbe
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
    {
        for(string& w : words)                    // prottek word er jonno
        {
            insertWord(w);                        // Trie te dhukao. sob word ekshathe ekta Trie te
        }
        vector<string> ans;                    // jei word gulo pabo ekhane jomabe
        int m = board.size();                     // row songkha
        int n = board[0].size();                  // column songkha
        for(int r = 0; r < m; r++)                // prottek row
        {
            for(int c = 0; c < n; c++)            // prottek column
            {
                dfs(board, r, c, root, ans);   // (r,c) theke DFS, Trie er root theke shuru. prottek cell e starting point hote pare
            }
        }
        return ans;                            
    }
};