/*
PROBLEM: Hash Map — Custom Implementation
DESCRIPTION: Implement a hash map from scratch (not std::unordered_map) using separate chaining
(array of buckets, each a vector of key-value pairs), with a simple hash function, supporting
insert/put, get, erase, contains, and dynamic resizing (rehash) when the load factor exceeds a
threshold.
CONSTRAINTS: General-purpose implementation over hashable key types (int and string demoed).
Operations should be correct for arbitrary sequences of calls, including overwriting an existing
key, erasing a missing key, and triggering multiple rehashes.
EXAMPLE INPUT/OUTPUT: See main() below for a runnable usage demo.
*/

/*
APPROACH:
Storage is a `vector<vector<pair<K,V>>>` — an array of buckets, each bucket a small vector of
key-value pairs that all hashed to the same index ("separate chaining" — collisions are resolved
by chaining multiple entries off one slot rather than probing elsewhere). The hash function uses
`std::hash<K>` (a reasonable, well-distributed general-purpose hash for ints/strings) reduced into
range via `% bucketCount`.

- put(key, val): compute the bucket index, linearly scan that bucket for an existing entry with
  the same key (update it in place if found), otherwise append a new pair. Then check the load
  factor (size / bucketCount); if it exceeds a threshold (0.75), rehash: double the bucket count
  and reinsert every existing entry into the new, larger bucket array. Amortized O(1) because
  rehashing happens only every ~O(current size) insertions and its O(n) cost is spread over those
  insertions (identical amortized argument to std::vector's doubling growth).
- get(key)/contains(key): compute the bucket index, linearly scan that bucket. O(1) average since
  buckets stay short (~load factor many entries) as long as the hash function spreads keys evenly;
  degrades to O(n) worst case if all keys collide into one bucket (e.g. a bad hash function).
- erase(key): scan the bucket, remove the matching entry if found (swap-and-pop or vector erase).

Load factor threshold of 0.75 is the classic balance point: too low wastes memory on mostly-empty
buckets, too high lets bucket chains grow long and degrade average-case O(1) lookups toward O(n).
*/

#include <bits/stdc++.h>
using namespace std;

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
        for (auto& bucket : buckets) {
            for (auto& kv : bucket) {
                size_t idx = bucketIndex(kv.first, newBucketCount);
                newBuckets[idx].push_back(move(kv));
            }
        }
        buckets = move(newBuckets);
    }

public:
    explicit HashMap(size_t initialBuckets = 8) : buckets(initialBuckets), count(0) {}

    void put(const K& key, const V& val) {
        size_t idx = bucketIndex(key, buckets.size());
        for (auto& kv : buckets[idx]) {
            if (kv.first == key) {
                kv.second = val;
                return;
            }
        }
        buckets[idx].push_back({key, val});
        count++;

        if ((double)count / buckets.size() > MAX_LOAD_FACTOR) {
            rehash();
        }
    }

    // Returns true and sets `out` if found; returns false otherwise.
    bool get(const K& key, V& out) const {
        size_t idx = bucketIndex(key, buckets.size());
        for (const auto& kv : buckets[idx]) {
            if (kv.first == key) {
                out = kv.second;
                return true;
            }
        }
        return false;
    }

    bool contains(const K& key) const {
        size_t idx = bucketIndex(key, buckets.size());
        for (const auto& kv : buckets[idx]) {
            if (kv.first == key) return true;
        }
        return false;
    }

    bool erase(const K& key) {
        size_t idx = bucketIndex(key, buckets.size());
        auto& bucket = buckets[idx];
        for (size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i].first == key) {
                bucket.erase(bucket.begin() + i);
                count--;
                return true;
            }
        }
        return false;
    }

    size_t size() const { return count; }
    size_t bucketCount() const { return buckets.size(); }
};

int main() {
    HashMap<string, int> map;

    map.put("apple", 1);
    map.put("banana", 2);
    map.put("cherry", 3);
    map.put("apple", 100); // overwrite existing key

    int val;
    cout << boolalpha;
    cout << "get(\"apple\"): " << map.get("apple", val) << ", value=" << val << endl; // true, 100
    cout << "get(\"banana\"): " << map.get("banana", val) << ", value=" << val << endl; // true, 2
    cout << "contains(\"cherry\"): " << map.contains("cherry") << endl; // true
    cout << "contains(\"durian\"): " << map.contains("durian") << endl; // false

    cout << "erase(\"banana\"): " << map.erase("banana") << endl; // true
    cout << "contains(\"banana\") after erase: " << map.contains("banana") << endl; // false
    cout << "erase(\"banana\") again: " << map.erase("banana") << endl; // false

    // Trigger a resize by inserting many keys.
    HashMap<int, int> bigMap(4);
    for (int i = 0; i < 50; i++) bigMap.put(i, i * i);
    cout << "size after 50 inserts: " << bigMap.size() << endl;         // 50
    cout << "bucketCount after resizes: " << bigMap.bucketCount() << endl; // > 4, grown via rehash
    int sq;
    bigMap.get(23, sq);
    cout << "get(23): " << sq << endl; // 529

    return 0;
}
