// Problem: Tweet Design
// Platform: NeetCode
// Link: https://neetcode.io/problems/design-twitter
// time complexity: O(log n); প্রতিটা push/pop O(1), r amra roughly n-bar এই operation করি
// space complexity:

/*
ধরি ৩ জন user:

User 1
User 2
User 3
Step 1: Tweets
postTweet(1, 101);
postTweet(2, 201);
postTweet(1, 102);
postTweet(3, 301);

প্রতিবার time++ হবে।

তাই:

Tweet	User	Time
101	1	1
201	2	2
102	1	3
301	3	4

আমাদের tweet map:

User 1 → (101,1), (102,3)
User 2 → (201,2)
User 3 → (301,4)
Step 2: Follow

ধরি:

follow(1, 2);
follow(1, 3);

তাহলে:

following[1] = {2, 3}

মানে User 1:

নিজে + User 2 + User 3
Step 3: getNewsFeed(1)

প্রথমে:

vector<int> user;
user.push_back(1);

তাই:

user = {1}

তারপর following থেকে:

following[1] = {2,3}

তাই:

user = {1,2,3}

অর্থাৎ আমাদের এই ৩ জনের tweet দেখতে হবে।

Step 4: সব Tweets বের করি
User 1
(101,1)
(102,3)
User 2
(201,2)
User 3
(301,4)

কিন্তু sorting সহজ করার জন্য আমরা (time, tweetId) রাখি।

তাই allTweets:

(1,101)
(3,102)
(2,201)
(4,301)
Step 5: Sort

আমরা করি:

sort(allTweets.rbegin(), allTweets.rend());

তাই:

(4,301)
(3,102)
(2,201)
(1,101)

কারণ বড় time = নতুন tweet।

Step 6: Tweet ID নিই

আমাদের দরকার tweetId, time না।

তাই .second নিই:

(4,301) → 301
(3,102) → 102
(2,201) → 201
(1,101) → 101

Final:

[301, 102, 201, 101]

এটাই getNewsFeed(1) return করবে।

আরেকটা খুব ছোট Example

ধরো:

User 1 → tweet 10 at time 1
User 2 → tweet 20 at time 2
User 2 → tweet 30 at time 3

User 1 follows User 2।

তাহলে:

user = {1,2}

Tweets:

User 1 → (10,1)
User 2 → (20,2), (30,3)

allTweets:

(1,10)
(2,20)
(3,30)

Sort:

(3,30)
(2,20)
(1,10)

Answer:

[30,20,10]
*/

class Twitter
{
public:

    // প্রতিটি নতুন tweet-এর জন্য একটি unique time রাখবো
    // প্রথম tweet -> time = 1
    // দ্বিতীয় tweet -> time = 2
    // তৃতীয় tweet -> time = 3
    int time = 0;

    // একজন user-এর সব tweet রাখবে
    // Key   = userId
    // Value = vector of (tweetId, time)
    // Example:
    // tweet[2] = {(12,1), (13,2)}
    // এখানে:
    // 12 = tweetId
    // 1  = tweet-এর time
    unordered_map<int, vector<pair<int, int>>> tweet;
    // কে কাকে follow করছে সেটা রাখবে
    // Key   = followerId
    // Value = যাদের follow করছে তাদের ID
    // Example:
    // following[2] = {3}
    // মানে User 2, User 3-কে follow করছে
    unordered_map<int, vector<int>> following;

    // Constructor
    Twitter()
    {

    }

    // নতুন tweet post করার function
    void postTweet(int userId, int tweetId)
    {
        // নতুন tweet আসলে time 1 বাড়বে
        time++;
        // (tweetId, time) হিসেবে tweet save করছি
        // Example:
        // postTweet(2, 12)
        // হলে:
        // tweet[2] = {(12, 1)}
        tweet[userId].push_back(make_pair(tweetId, time));
    }

    // News Feed বের করার function
    vector<int> getNewsFeed(int userId)
    {
        // এখানে নিজের userId
        // এবং যাদের follow করি তাদের userId রাখবো
        vector<int> user;
        // নিজের tweets অবশ্যই News Feed-এ থাকবে
        user.push_back(userId);
        // যাদের follow করি তাদের ID বের করছি
        for(int i = 0; i < following[userId].size(); i++)
        {
            user.push_back(following[userId][i]);
        }
        // সব users-এর সব tweets এখানে রাখবো
        // এখানে pair হবে:
        // first  = time
        // second = tweetId
        // কারণ time অনুযায়ী sort করতে চাই
        vector<pair<int, int>> allTweets;
        // user vector-এর প্রত্যেক user-এর জন্য loop
        for(int i = 0; i < user.size(); i++)
        {
            // ঐ user-এর সব tweets-এর জন্য loop
            for(int j = 0; j < tweet[user[i]].size(); j++)
            {
                // Original tweet structure:
                // tweet[user[i]][j].first = tweetId
                int tweetId = tweet[user[i]][j].first;
                // tweet[user[i]][j].second= time
                int tweetTime = tweet[user[i]][j].second;
                // এবার (time, tweetId) হিসেবে save করছি
                // Example: original = (13, 2)
                // allTweets-এ যাবে: (2, 13)
                allTweets.push_back(make_pair(tweetTime, tweetId));
            }
        }

        // Latest tweet আগে আনতে হবে
        // rbegin() থেকে rend() পর্যন্ত sort করলে
        // descending order হবে
        // Example: (1,12), (2,13), (3,14), (4,15)
        // হবে: (4,15), (3,14), (2,13), (1,12)
        sort(allTweets.rbegin(),allTweets.rend());
        // Final answer রাখার vector
        vector<int> ans;
        // সর্বোচ্চ 10টি latest tweet নিতে হবে
        for(int i = 0; i < allTweets.size() && i < 10; i++)
        {
            // allTweets[i].first = time
            // allTweets[i].second = tweetId
            // তাই tweetId নেওয়ার জন্য .second
            ans.push_back(allTweets[i].second);
        }
        // Final News Feed return করছি
        return ans;
    }

    // followerId -> followeeId follow করবে
    void follow(int followerId, int followeeId)
    {
        // একই user আগে থেকেই follow করা আছে কিনা সেটা check করছি
        for(int i = 0; i < following[followerId].size(); i++)
        {
            // যদি followeeId আগে থেকেই থাকে
            if(following[followerId][i] == followeeId)
            {
                // আবার add করবো না
                return;
            }
        }
        // আগে follow না করলে এখানে add হবে
        following[followerId].push_back(followeeId);
    }

    // followerId -> followeeId unfollow করবে
    void unfollow(int followerId, int followeeId)
    {
        // follower-এর following list-এর উপর loop
        for(int i = 0; i < following[followerId].size(); i++)
        {
            // followeeId পাওয়া গেলে
            if(following[followerId][i] == followeeId)
            {
                // vector থেকে remove করছি
                following[followerId].erase(following[followerId].begin() + i);
                // কাজ শেষ, তাই loop বন্ধ
                break;
            }
        }
    }
};