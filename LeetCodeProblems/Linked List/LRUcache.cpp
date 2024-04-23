#include <unordered_map>
#include <list>

class LRUCache {
    private:
        int capacity;
        std::unordered_map<int, std::pair<int, std::list<int>::iterator>> cache;
        std::list<int> lru; // Doubly linked list to maintain order of usage

    public:
        LRUCache(int capacity) {
            this->capacity = capacity;
        }

        int get(int key) {
            if (cache.find(key) != cache.end()) {
                // Key found in cache, update its position in LRU list
                auto it = cache[key].second;
                lru.erase(it);
                lru.push_front(key);
                cache[key].second = lru.begin();
                return cache[key].first; // Return the value associated with the key
            }
            return -1; // Key not found
        }

        void put(int key, int value) {
            if (cache.find(key) != cache.end()) {
                // Key already exists, update its value and position in LRU list
                auto it = cache[key].second;
                lru.erase(it);
                lru.push_front(key);
                cache[key] = {value, lru.begin()};
            } else {
                // Key doesn't exist, insert a new key-value pair
                if (cache.size() == capacity) {
                    // Cache is full, evict the least recently used item
                    int leastRecentlyUsed = lru.back();
                    lru.pop_back();
                    cache.erase(leastRecentlyUsed);
                }
                // Insert new key-value pair into cache and LRU list
                lru.push_front(key);
                cache[key] = {value, lru.begin()};
            }
        }
};