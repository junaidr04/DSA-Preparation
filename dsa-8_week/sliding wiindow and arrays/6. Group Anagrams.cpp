// Time: O(n * k log k)  -> n ta string, protita sort e k log k
// Space: O(n * k)       -> shob string map e store hoy

/*  
Step 1: Prothome shob string er key ber kori
Original	Sort korar por (key)
eat	        e,a,t → a,e,t → “aet”
tea	        t,e,a → a,e,t → “aet”
ate	        a,t,e → a,e,t → “aet”
tan	        t,a,n → a,n,t → “ant”
nat	        n,a,t → a,n,t → “ant”
bat	        b,a,t → a,b,t → “abt”

Dekho, eat, tea, ate tinta-i “aet” hoyeche. tan, nat duita “ant”. bat ekla “abt”.

Step 2: Loop e map grp kivabe bhorche

Start: grp = {} (faka)

Loop	s	    key (sort er por)	grp[key].push_back(s) er por grp
1	    eat	    aet	                aet → [eat]
2	    tea	    aet	                aet → [eat, tea]
3	    tan	    ant	                aet → [eat, tea], ant → [tan]
4	    ate	    aet	                aet → [eat, tea, ate], ant → [tan]
5	    nat	    ant	                aet → [eat, tea, ate], ant → [tan, nat]
6	    bat	    abt	                aet → [eat, tea, ate], ant → [tan, nat], abt → [bat]

Dhorar moto point: key ta already map e thakle grp[key] oi purano bucket e s jog kore. Na thakle grp[key] automatic notun bucket banay. Tai alada if check lagbe na.

Step 3: Map theke ans banano
grp:
  "aet" → [eat, tea, ate]
  "ant" → [tan, nat]
  "abt" → [bat]

for (auto &p : grp) diye protibar p.second (group ta) ans e push hoy:

Loop	p.first (key)	p.second (group)	ans
1	    aet	            [eat, tea, ate]	    [[eat,tea,ate]]
2	    ant	            [tan, nat]	        [[eat,tea,ate], [tan,nat]]
3	    abt	            [bat]	            [[eat,tea,ate], [tan,nat], [bat]]

p.first (key) ta ar lagche na, shudhu bucket tuku lagche. Order alada hote pare (unordered_map), problem e order chay na.

Calculation (complexity), example diye

n = 6 ta string, protita length k = 3.

Protita string sort: k log k = 3 × log 3 ≈ choto kaj.
6 ta string er jonno: n × k log k.
Map e insert/lookup: key er length k, tai hash korte O(k), n bar mile O(n·k) (sort er cheye kom, tai dhorte hobe na).
*/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // grp: key = sorted string (chhap), value = oi chhap er shob original string
        // jemon: "aet" -> [eat, tea, ate]
        unordered_map<string, vector<string>> grp;
        for (string& s : strs)
        {
            // original s ke bodlabo na, tai copy e sort korbo
            string key = s;
            // sort korle shob anagram ek e key hoye jay
            // eat, tea, ate -> shobai "aet"
            sort(key.begin(), key.end());
            // key age thakle purano bucket e jog hobe, na thakle notun bucket toiri hobe
            // NOTE: push_back e original s jabe, key na
            grp[key].push_back(s);
        }
        // map theke answer banano: shudhu group gulo dorkar, key na
        vector<vector<string>> ans;
        for (auto &p : grp)
        {
            ans.push_back(p.second);   // p.first = key (lagbe na), p.second = group
        }
        return ans;
    }
};
