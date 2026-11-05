// TC: O(N log K); linked list-এর total node count = N, এবং heap size = K, তাই push/pop cost = O(log K)
// SC: O(K); heap-এর size = K


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution
{
public:
    // Min Heap-এর জন্য Custom Comparator
    struct compare
    {
        bool operator()(ListNode* a, ListNode* b)
        {
            // যার value ছোট, তাকে আগে বের করবে
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        // Step 1: Min Heap তৈরি
        // Heap-এর ভিতরে ListNode pointer থাকবে
        priority_queue<ListNode*, vector<ListNode*>, compare> pq;
        // Step 2: প্রতিটি Linked List-এর প্রথম Node Heap-এ রাখব
        for(int i = 0; i < lists.size(); i++)
        {
            // List empty না হলে
            if(lists[i] != nullptr)
            {
                // সেই List-এর প্রথম Node Heap-এ push করব
                pq.push(lists[i]);
            }
        }

        // Step 3: Dummy Node তৈরি.. Result Linked List তৈরির জন্য
        ListNode* dummy = new ListNode(0);

        // curr দিয়ে Result List-এর শেষ Node track করব
        ListNode* curr = dummy;

        // Step 4: Heap empty না হওয়া পর্যন্ত চলবে
        while(!pq.empty())
        {
            // Heap-এর সবচেয়ে ছোট Node বের করব
            ListNode* top = pq.top();

            // Heap থেকে Node সরিয়ে দেব
            pq.pop();

            // Step 5: Node-টিকে Result List-এ যুক্ত করব
            curr->next = top;

            // curr-কে সামনে এগিয়ে নেব
            curr = curr->next;

            // Step 6: বের করা Node-এর next Node Heap-এ পাঠাব
            if(top->next != nullptr)
            {
                pq.push(top->next);
            }

            // Step 7: পুরোনো next link বিচ্ছিন্ন করব
            // পরের iteration-এ Result List-এর link ঠিক রাখবে
            curr->next = nullptr;
        }

        // Step 8: Dummy বাদ দিয়ে আসল Head return করব
        return dummy->next;
    }
};