// time: O(1), put: O(1)
// Space: O(capacity)

/*
Summary table
Step	Kaj	        List (front → back)	    Return
1	    put(1,1)	1	                    -
2	    put(2,2)	2, 1	                -
3	    (1)	        1, 2	                1
4	    put(3,3)	3, 1 (2 evict)	        -
5	    get(2)	    3, 1	                -1  
*/

class LRUCache
{
    // list er ekta node: key + val + duto dik er pointer
    struct Node
    {
        int key, val;
        Node* prev;   // bam pase ke
        Node* next;   // dan pase ke
        // prev/next shuru te nullptr
        Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
    };
    int cap;                          // cache e max koto ta entry thakbe
    unordered_map<int, Node*> mp;     // key -> list er node (O(1) e node pawar shortcut)
    Node* head;                       // dummy head, er pase = shobcheye RECENT
    Node* tail;                       // dummy tail, er ager = shobcheye PURANO

    // node ke head er thik pore boshao (mane recent banao)
    void addToFront(Node* node)
    {
        node->next = head->next;      // 1. X (ager first node) ke age save, noile harabe
        node->prev = head;            // 2. node er bam pase HEAD
        head->next->prev = node;      // 3. X er bam pase ekhon node
        head->next = node;            // 4. HEAD er dan pase ekhon node (shobar shesh e)
    }

    // node ke list theke khule nao, A <-> node <-> B theke A <-> B
    void removeNode(Node* node)
    {
        node->prev->next = node->next;   // A er next = B
        node->next->prev = node->prev;   // B er prev = A
    }

public:
    LRUCache(int capacity)
    {
        cap = capacity;
        head = new Node(0, 0);        // dummy node, key/val er kono matter nai
        tail = new Node(0, 0);
        head->next = tail;            // faka list: HEAD <-> TAIL
        tail->prev = head;
    }

    int get(int key)
    {
        // key map e nai hole -1
        if (mp.find(key) == mp.end())
            return -1;

        Node* node = mp[key];         // key diye sathe sathe node pelam
        removeNode(node);             // age purano jayga theke khulo
        addToFront(node);             // pore front e boshao (ekhon recent)
        return node->val;
    }

    void put(int key, int value)
    {
        if (mp.find(key) != mp.end())
        {
            // key already ache: notun node na, shudhu value update + recent
            Node* node = mp[key];
            node->val = value;
            removeNode(node);
            addToFront(node);
        }
        else
        {
            // key nai, cache full hole age shobcheye purano ta evict
            if (mp.size() == cap)
            {
                Node* lru = tail->prev;     // TAIL er ager node = shobcheye purano
                removeNode(lru);            // list theke khulo
                mp.erase(lru->key);         // NOTE: map theke o muchte hobe (ei jonnoi node e key rakhi)
                delete lru;                 // memory free, NOTE: erase age, delete pore
            }

            // notun node banao, front e boshao, map e rakho
            Node* node = new Node(key, value);
            addToFront(node);
            mp[key] = node;
        }
    }
};
