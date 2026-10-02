/*
PROBLEM: Trie (Prefix Tree) — Custom Implementation
DESCRIPTION: Implement a trie from scratch, supporting insert(word), search(word), and
startsWith(prefix), without relying on any STL string-set/map as the underlying storage
mechanism for the tree structure itself.
CONSTRAINTS: General-purpose implementation; assume lowercase English letters ('a'-'z').
Operations should be correct for arbitrary sequences of calls (inserting duplicates, empty
strings, searching for words never inserted, etc.).
EXAMPLE INPUT/OUTPUT: See main() below for a runnable usage demo.
*/

/*
APPROACH:
Each TrieNode holds a fixed-size array of 26 child pointers (one per lowercase letter) and a
boolean `isEndOfWord` flag. Starting from the root (which represents the empty prefix), insert(word)
walks the word character by character, creating a child node whenever the needed edge doesn't yet
exist, then marks the final node's isEndOfWord flag true. search(word) walks the same way but returns
false immediately if any required child is missing, and only returns true if it reaches the end AND
that final node is marked as a word-end (this distinguishes a full word from a mere prefix of some
other word). startsWith(prefix) is identical to search but does not require isEndOfWord — reaching
the end of the prefix path is enough. All three operations are O(L) where L is the length of the
word/prefix, since each character requires exactly one O(1) array-index step down the tree. The
26-pointer array trades memory for O(1) child lookups; a map-based alternative would use less memory
but add a log(26) or hashing overhead per character.
*/

#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }

    ~TrieNode() {
        for (int i = 0; i < 26; i++) delete children[i];
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
        node->isEndOfWord = true;
    }

    bool search(const string& word) const {
        TrieNode* node = findNode(word);
        return node != nullptr && node->isEndOfWord;
    }

    bool startsWith(const string& prefix) const {
        return findNode(prefix) != nullptr;
    }

private:
    // Walks the tree following `s`; returns the node reached, or nullptr if the path breaks.
    TrieNode* findNode(const string& s) const {
        TrieNode* node = root;
        for (char c : s) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr) return nullptr;
            node = node->children[idx];
        }
        return node;
    }
};

int main() {
    Trie trie;

    trie.insert("apple");
    trie.insert("app");
    trie.insert("apply");
    trie.insert("bat");

    cout << boolalpha;
    cout << "search(\"apple\"): " << trie.search("apple") << endl;     // true
    cout << "search(\"app\"): " << trie.search("app") << endl;         // true
    cout << "search(\"appl\"): " << trie.search("appl") << endl;       // false (only a prefix)
    cout << "search(\"bat\"): " << trie.search("bat") << endl;         // true
    cout << "search(\"batman\"): " << trie.search("batman") << endl;   // false

    cout << "startsWith(\"app\"): " << trie.startsWith("app") << endl;   // true
    cout << "startsWith(\"appl\"): " << trie.startsWith("appl") << endl; // true
    cout << "startsWith(\"b\"): " << trie.startsWith("b") << endl;       // true
    cout << "startsWith(\"cat\"): " << trie.startsWith("cat") << endl;   // false

    return 0;
}
