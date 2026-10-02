# Hash Map (Separate Chaining)

## Overview
A hash map stores key-value pairs in a fixed-size array of "buckets". A hash function maps each key to a bucket index (`hash(key) % bucket_count`). Because different keys can hash to the same bucket (a collision), each bucket holds a small container (here, a `std::vector` of key-value pairs) of all entries that landed there — this is "separate chaining". Lookups compute the bucket index, then linearly scan that bucket's (usually short) list for the matching key. When the ratio of stored elements to bucket count (the load factor) exceeds a threshold, the table resizes (doubles bucket count) and rehashes every existing entry into the new, larger table, keeping buckets short and operations fast on average.

## Operations & Complexity
| Operation | Time (avg) | Time (worst) | Space |
|---|---|---|---|
| insert/put | O(1) amortized | O(n) | O(1) amortized (O(n) during rehash) |
| get | O(1) | O(n) | O(1) |
| erase | O(1) | O(n) | O(1) |
| contains | O(1) | O(n) | O(1) |
| rehash (triggered) | O(n) | O(n) | O(n) new table |

Average-case O(1) assumes a reasonably uniform hash function spreading keys evenly across buckets. Worst case O(n) happens with a bad/adversarial hash function that funnels all keys into one bucket, degenerating each bucket into a linear list.

## When It's Used in Interviews
- Fast membership/lookup problems (two-sum, deduplication).
- Grouping/counting problems (group anagrams, frequency counting).
- Caching (LRU cache combines a hash map with a linked list).
- Anytime you need average O(1) key -> value association and don't need sorted order.
- "Design a data structure" prompts (Design HashMap/HashSet) that test understanding of what `std::unordered_map` does internally.

## Trade-offs
- vs balanced BST/map: a BST-backed map (e.g. `std::map`) gives O(log n) operations but keeps keys sorted and has guaranteed worst case; a hash map is faster on average but has no ordering and degrades to O(n) worst case.
- vs open addressing (linear/quadratic probing, robin hood hashing): separate chaining tolerates high load factors more gracefully and simplifies deletion, but has extra pointer/vector overhead per bucket versus the better cache locality of open addressing.
- Hash quality matters: a poor hash function increases collision chains and can be exploited (hash-flooding attacks) to force worst-case O(n) behavior; production hash maps use randomized/seeded hash functions to mitigate this.
