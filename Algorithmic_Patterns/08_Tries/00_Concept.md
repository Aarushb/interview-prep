# Tries

## Pattern Overview
A trie (prefix tree) is a tree where each edge represents a character and each root-to-node path represents a prefix, making it the go-to structure for prefix search, autocomplete, and dictionary-based word matching. Insert, search, and startsWith all walk the tree one character at a time in O(L) time, and tries shine when layered as an optimization onto DFS/backtracking searches that need to prune against a large word list.

## When to Use It
- The problem involves prefix search, autocomplete, or "startsWith" queries.
- You're given a large dictionary/list of words and need to repeatedly check membership or prefix membership efficiently.
- The problem explicitly mentions wildcard pattern matching over a word list (e.g., `.` matches any character).
- Many words in the input share common prefixes, and you want to avoid re-processing shared prefixes repeatedly (e.g., pruning a grid DFS/backtracking search using a dictionary — Word Search II).
- You need to find the longest common prefix among a set of strings, or the shortest unique prefix per word.
- A hash set would work but you specifically need prefix-awareness that a hash set can't give you (hash sets only support exact-match lookups, not "does any word start with this?").

## Core Idea
A trie (prefix tree) is a tree where each edge represents one character, and each root-to-node path represents the prefix spelled out by the edges along that path. Nodes are typically represented with either a fixed-size array of children (e.g., `array<TrieNode*, 26>` for lowercase a-z, giving O(1) child lookup) or an `unordered_map<char, TrieNode*>` when the alphabet is large or sparse (worse constant factor, but no wasted memory for unused letters). Each node also carries an `isEndOfWord` (or `end`) boolean flag, which distinguishes "this path is a prefix of some word" from "this path spells out a complete word" — a node can be both, or neither, or just one.

The three core operations all follow the same walking pattern: start at the root, and for each character in the query string, step to the corresponding child (creating it if it doesn't exist, for insert), failing immediately if that child doesn't exist (for search/startsWith). `insert(word)` walks/creates nodes character by character and marks the final node's `end` flag true. `search(word)` walks the same way but returns false if the walk ever fails to find a child, and only returns true if it reaches the end of the word AND that final node's `end` flag is set. `startsWith(prefix)` is identical to search except it doesn't check the `end` flag — reaching the end of the prefix string via a valid path is success regardless of whether a complete word ends there.

Beyond the basic three operations, tries shine as an optimization layered onto another technique. In "Word Search II"-style problems, instead of checking each candidate word individually against the board (which repeats work for words sharing prefixes), you insert all target words into a trie once, then do a single DFS/backtracking pass over the board that walks the trie alongside the grid — abandoning a branch the instant the current path no longer matches any trie edge. This turns what would be `O(words * board cells)` into something much closer to `O(board cells * average word length)`, because shared prefixes are explored only once. Wildcard matching (e.g., "Add and Search Word") extends the search DFS so that a literal character follows exactly one trie edge, while a wildcard character fans out and recurses into every non-null child at that trie level.

## Complexity
- Time: O(L) per insert/search/startsWith, where L is the length of the word/prefix being processed — independent of how many words are already stored. Building a trie from n words of average length L costs O(n · L).
- Space: O(total characters across all inserted words) in the worst case (no shared prefixes), but can be much less when words share prefixes since shared nodes are stored once. A 26-ary array per node costs O(26) pointers per node regardless of how many are actually used, which can waste memory versus a hash-map-based node for sparse alphabets.

## C++ Template
```cpp
struct TrieNode {
    bool isEndOfWord = false;
    array<TrieNode*, 26> children{}; // value-initialized to nullptr
};

class Trie {
public:
    Trie() : root(new TrieNode()) {}

    void insert(const string& word) {
        TrieNode* cur = root;
        for (char c : word) {
            int i = c - 'a';
            if (!cur->children[i]) cur->children[i] = new TrieNode();
            cur = cur->children[i];
        }
        cur->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* node = traverse(word);
        return node != nullptr && node->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        return traverse(prefix) != nullptr;
    }

private:
    TrieNode* root;

    // Walks the trie following `s`; returns the final node reached, or nullptr if the path breaks.
    TrieNode* traverse(const string& s) {
        TrieNode* cur = root;
        for (char c : s) {
            int i = c - 'a';
            if (!cur->children[i]) return nullptr;
            cur = cur->children[i];
        }
        return cur;
    }
};

// --- Wildcard search pattern (e.g. Add and Search Word), where '.' matches any character ---
bool wildcardSearch(const string& word, int idx, TrieNode* node) {
    if (!node) return false;
    if (idx == (int)word.size()) return node->isEndOfWord;

    char c = word[idx];
    if (c == '.') {
        for (TrieNode* child : node->children)
            if (child && wildcardSearch(word, idx + 1, child)) return true;
        return false;
    }
    return wildcardSearch(word, idx + 1, node->children[c - 'a']);
}
```

## Common Pitfalls
- Forgetting to check `isEndOfWord` in `search`, which silently turns `search` into `startsWith` and produces false positives for prefixes that aren't actually complete words.
- Not null-checking a child pointer before dereferencing it while walking the trie — array-based nodes default-initialize pointers to `nullptr`, so an unset branch must be checked explicitly, not assumed.
- Using a fixed-size `array<TrieNode*, 26>` for problems where the alphabet includes uppercase letters, digits, or other characters, causing out-of-bounds array indexing (`c - 'a'` producing a negative or >25 index).
- Rebuilding a trie from scratch for every query instead of building it once and reusing it — trie-based approaches only pay off when the one-time construction cost is amortized over many lookups.
- Leaking memory by never freeing trie nodes in languages/contexts where that matters (usually acceptable to skip in an interview, but worth mentioning you're aware of it).
- Reaching for a trie when a plain `unordered_set`/`unordered_map` would suffice — if the problem never needs prefix-level queries (only exact membership), a hash set is simpler and just as fast.
