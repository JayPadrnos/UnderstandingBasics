#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <algorithm>

using namespace std;

class Twitter {
public:
    Twitter() {
        time = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        tweets[userId].emplace_front(time++, tweetId);
    }
    
    vector<int> getNewsFeed(int userId) {
        priority_queue<pair<int, int>> max_heap;

        addTweetsToHeap(userId, max_heap);

        if (following.find(userId) != following.end()) {
            for (int followeeId : following[userId]) {
                addTweetsToHeap(followeeId, max_heap);
            }
        }

        vector<int> newsFeed;
        while (!max_heap.empty() && newsFeed.size() < 10) {
            newsFeed.push_back(max_heap.top().second);
            max_heap.pop();
        }

        return newsFeed;
    }
    
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            following[followerId].insert(followeeId);
        }
    }
    
    void unfollow(int followerId, int followeeId) {
        if (following.find(followerId) != following.end()) {
            following[followerId].erase(followeeId);
        }
    }

private:
    int time;
    unordered_map<int, deque<pair<int, int>>> tweets;
    unordered_map<int, unordered_set<int>> following;

    void addTweetsToHeap(int userId, priority_queue<pair<int, int>>& heap) {
        if (tweets.find(userId) != tweets.end()) {
            for (const auto& tweet : tweets[userId]) {
                heap.push(tweet);
            }
        }
    }
};
