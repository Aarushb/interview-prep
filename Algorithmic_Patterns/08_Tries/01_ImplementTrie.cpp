/*
PROBLEM: Implement Trie (Prefix Tree)
DESCRIPTION: Design a trie with insert, search, and startsWith for lowercase a-z.
CONSTRAINTS:
- 1 <= word.length, prefix.length <= 2000
- word and prefix consist only of lowercase English letters.
- At most 3 * 10^4 calls in total will be made to insert, search, and startsWith.
EXAMPLE INPUT/OUTPUT:
Input: insert("apple"), search("apple") -> true, search("app") -> false, startsWith("app") -> true, insert("app"), search("app") -> true
*/

/*
APPROACH:
A trie stores one character per edge so every node represents a prefix shared by all words
that pass through it. Insert walks/creates nodes character by character and marks the final
node as end-of-word; search does the same walk but also checks the end flag, while
startsWith only cares that the path exists at all. Using a fixed array<TrieNode*,26> gives
O(1) child lookup per character since the alphabet is restricted to lowercase a-z.
*/

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    bool end = false;
    array<TrieNode*, 26> next{};
    TrieNode() { next.fill(nullptr); }
};

class Trie {
public:
    Trie(): root(new TrieNode()) {}
    void insert(const string& word) {
        TrieNode* cur = root;
        for (char c : word) {
            int i = c - 'a';
            if (!cur->next[i]) cur->next[i] = new TrieNode();
            cur = cur->next[i];
        }
        cur->end = true;
    }
    bool search(const string& word) {
        TrieNode* cur = traverse(word);
        return cur && cur->end;
    }
    bool startsWith(const string& prefix) {
        return traverse(prefix) != nullptr;
    }
private:
    TrieNode* root;
    TrieNode* traverse(const string& s) {
        TrieNode* cur = root;
        for (char c : s) {
            int i = c - 'a';
            if (!cur->next[i]) return nullptr;
            cur = cur->next[i];
        }
        return cur;
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    cout << boolalpha;
    cout << trie.search("apple") << "\n";     // true
    cout << trie.search("app") << "\n";       // false
    cout << trie.startsWith("app") << "\n";    // true
    trie.insert("app");
    cout << trie.search("app") << "\n";       // true
    return 0;
}
