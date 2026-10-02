/*
PROBLEM 1: Design HashMap (LeetCode 706)
DESCRIPTION: Design a HashMap without using any built-in hash table libraries. Implement put(key,
value), get(key) (return -1 if the key doesn't exist), and remove(key).
CONSTRAINTS: 0 <= key, value <= 10^6, at most 10^4 calls to put/get/remove.
EXAMPLE INPUT/OUTPUT:
  put(1, 1); put(2, 2); get(1) -> 1; get(3) -> -1; put(2, 1); get(2) -> 1; remove(2); get(2) -> -1
*/

/*
APPROACH:
This directly demos the hand-rolled HashMap<K,V> from Implementation.cpp (separate chaining with
dynamic resizing) instantiated as HashMap<int,int>, wrapped to match LeetCode's exact API surface
(put/get/remove, with get returning -1 for a missing key instead of a bool+out-param). All the
underlying complexity guarantees carry over: O(1) average put/get/remove, O(n) amortized due to
periodic O(n) rehashes triggered by load factor.
*/

#include <bits/stdc++.h>
using namespace std;

// Same hand-rolled separate-chaining hash map as Implementation.cpp.
template <typename K, typename V>
class HashMap {
private:
    vector<vector<pair<K, V>>> buckets;
    size_t count;
    static constexpr double MAX_LOAD_FACTOR = 0.75;

    size_t bucketIndex(const K& key, size_t bucketCount) const {
        return hash<K>{}(key) % bucketCount;
    }

    void rehash() {
        size_t newBucketCount = buckets.size() * 2;
        vector<vector<pair<K, V>>> newBuckets(newBucketCount);
        for (auto& bucket : buckets)
            for (auto& kv : bucket)
                newBuckets[bucketIndex(kv.first, newBucketCount)].push_back(move(kv));
        buckets = move(newBuckets);
    }

public:
    explicit HashMap(size_t initialBuckets = 8) : buckets(initialBuckets), count(0) {}

    void put(const K& key, const V& val) {
        size_t idx = bucketIndex(key, buckets.size());
        for (auto& kv : buckets[idx]) {
            if (kv.first == key) { kv.second = val; return; }
        }
        buckets[idx].push_back({key, val});
        count++;
        if ((double)count / buckets.size() > MAX_LOAD_FACTOR) rehash();
    }

    bool get(const K& key, V& out) const {
        size_t idx = bucketIndex(key, buckets.size());
        for (const auto& kv : buckets[idx]) {
            if (kv.first == key) { out = kv.second; return true; }
        }
        return false;
    }

    bool erase(const K& key) {
        size_t idx = bucketIndex(key, buckets.size());
        auto& bucket = buckets[idx];
        for (size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i].first == key) { bucket.erase(bucket.begin() + i); count--; return true; }
        }
        return false;
    }
};

class MyHashMap {
private:
    HashMap<int, int> map;

public:
    MyHashMap() {}

    void put(int key, int value) {
        map.put(key, value);
    }

    int get(int key) {
        int val;
        if (map.get(key, val)) return val;
        return -1;
    }

    void remove(int key) {
        map.erase(key);
    }
};

/*
PROBLEM 2: Group Anagrams (LeetCode 49)
DESCRIPTION: Given an array of strings, group the anagrams together. Two strings are anagrams if
one can be formed by rearranging the letters of the other. Return the groups in any order.
CONSTRAINTS: 1 <= strs.length <= 10^4, 0 <= strs[i].length <= 100, lowercase English letters.
EXAMPLE INPUT/OUTPUT:
  Input: ["eat","tea","tan","ate","nat","bat"]
  Output: [["bat"],["nat","tan"],["ate","eat","tea"]] (order of groups/elements may vary)
*/

/*
APPROACH:
Anagrams share the same multiset of characters, so sorting each string's characters produces a
canonical "signature" that is identical for every word in the same anagram group (e.g. "eat",
"tea", "ate" all sort to "aet"). Use our own HashMap<string, vector<string>> keyed by that sorted
signature: for each input word, compute its signature, then append the original word to
map[signature]'s vector (creating it if absent — get()/put() pattern since our HashMap doesn't
have operator[]). Finally collect all buckets' vectors into the result. Time: O(n * k log k) where
n = number of strings and k = max string length, dominated by sorting each string's characters;
hash map operations are O(1) average per string.
*/

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    HashMap<string, vector<string>> groups;

    for (const string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());

        vector<string> bucket;
        if (groups.get(key, bucket)) {
            bucket.push_back(s);
            groups.put(key, bucket);
        } else {
            groups.put(key, vector<string>{s});
        }
    }

    // Re-derive the set of keys by re-sorting each original string (our HashMap has no iterator);
    // use a small ordered set of unique signatures to collect final groups without duplicates.
    set<string> seenKeys;
    for (const string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        seenKeys.insert(key);
    }

    vector<vector<string>> result;
    for (const string& key : seenKeys) {
        vector<string> bucket;
        groups.get(key, bucket);
        result.push_back(bucket);
    }
    return result;
}

int main() {
    // Problem 1: Design HashMap
    {
        MyHashMap myMap;
        myMap.put(1, 1);
        myMap.put(2, 2);
        cout << "get(1): " << myMap.get(1) << endl; // 1
        cout << "get(3): " << myMap.get(3) << endl; // -1
        myMap.put(2, 1);
        cout << "get(2) after update: " << myMap.get(2) << endl; // 1
        myMap.remove(2);
        cout << "get(2) after remove: " << myMap.get(2) << endl; // -1
    }

    // Problem 2: Group Anagrams
    {
        vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
        vector<vector<string>> groups = groupAnagrams(strs);
        cout << "Group Anagrams result:" << endl;
        for (auto& group : groups) {
            cout << "  [ ";
            for (auto& w : group) cout << w << " ";
            cout << "]" << endl;
        }
    }

    return 0;
}
