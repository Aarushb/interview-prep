/*
PROBLEM 1: Longest Word in Dictionary (LeetCode 720)
DESCRIPTION: Given an array of strings `words` representing an English dictionary, find the
longest word in `words` that can be built one character at a time by other words in `words`
(i.e. every proper prefix of the word, at every length, must also exist in `words`). If there is
a tie for the longest word, return the lexicographically smallest one. If no such word exists,
return the empty string.
CONSTRAINTS: 1 <= words.length <= 1000, 1 <= words[i].length <= 30, lowercase English letters.
EXAMPLE INPUT/OUTPUT:
  Input: ["w","wo","wor","worl","world"]
  Output: "world" (built up one letter at a time via "w"->"wo"->"wor"->"worl"->"world")
  Input: ["a","banana","app","appl","ap","apply","apple"]
  Output: "apple"
*/

/*
APPROACH:
Insert every word into a trie, marking isEndOfWord at each word's terminal node (same trie as
Implementation.cpp). A word is "buildable one character at a time" exactly when every node along
its root-to-leaf path (except the root itself) is marked isEndOfWord — i.e. every prefix of it was
itself separately inserted as a complete word. So do a DFS/BFS over the trie: at each node, only
descend into a child if that child is marked isEndOfWord (this enforces the "buildable" chain
property), and track the longest such reachable word, breaking length ties by lexicographic order.
Sorting `words` first and inserting in sorted order lets a simpler single pass work too, but the
explicit trie-DFS generalizes better and reuses the trie abstraction. Time: O(sum of word lengths)
to build the trie plus O(number of trie nodes) to DFS it, both linear in total input size.
*/

#include <bits/stdc++.h>
using namespace std;

class TrieNode720 {
public:
    TrieNode720* children[26];
    bool isEndOfWord;
    TrieNode720() : isEndOfWord(false) {
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
    ~TrieNode720() {
        for (int i = 0; i < 26; i++) delete children[i];
    }
};

class LongestWordSolver {
private:
    TrieNode720* root;

    void insert(const string& word) {
        TrieNode720* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode720();
            node = node->children[idx];
        }
        node->isEndOfWord = true;
    }

    // DFS: only descend through children that are themselves complete words.
    void dfs(TrieNode720* node, string& path, string& best) {
        if (path.length() > best.length() ||
            (path.length() == best.length() && path < best)) {
            best = path;
        }
        for (int c = 0; c < 26; c++) {
            if (node->children[c] && node->children[c]->isEndOfWord) {
                path.push_back('a' + c);
                dfs(node->children[c], path, best);
                path.pop_back();
            }
        }
    }

public:
    LongestWordSolver() { root = new TrieNode720(); }
    ~LongestWordSolver() { delete root; }

    string longestWord(vector<string>& words) {
        for (const string& w : words) insert(w);
        string path, best;
        dfs(root, path, best);
        return best;
    }
};

/*
PROBLEM 2: Replace Words (LeetCode 648)
DESCRIPTION: Given a dictionary of word "roots" and a sentence, replace every word in the
sentence with its shortest root in the dictionary that is a prefix of it. If a word has no root in
the dictionary, leave it unchanged.
CONSTRAINTS: 1 <= roots.length <= 1000, 1 <= roots[i].length <= 100, sentence has 1 <= words <=
1000 words separated by single spaces, all lowercase.
EXAMPLE INPUT/OUTPUT:
  Input: roots = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
  Output: "the cat was rat by the bat"
*/

/*
APPROACH:
Insert every root into a trie. For each word in the sentence, walk the trie character by character
along the word: the first time we reach a node marked isEndOfWord, that prefix is the SHORTEST
matching root (because we stop walking as soon as we hit a complete root), so we replace the word
with that prefix. If we walk off the trie (a needed child is missing) or exhaust the word without
ever hitting isEndOfWord, the word is left unchanged. Time: O(total characters in the sentence)
since each word is scanned at most once, character by character, against the trie.
*/

class ReplaceWordsSolver {
private:
    TrieNode720* root;

    void insert(const string& word) {
        TrieNode720* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode720();
            node = node->children[idx];
        }
        node->isEndOfWord = true;
    }

    // Returns the shortest root prefix of `word`, or `word` itself if none found.
    string findRoot(const string& word) {
        TrieNode720* node = root;
        string prefix;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) return word; // no matching root
            prefix.push_back(c);
            node = node->children[idx];
            if (node->isEndOfWord) return prefix; // shortest root found
        }
        return word; // walked the whole word, never hit a root
    }

public:
    ReplaceWordsSolver() { root = new TrieNode720(); }
    ~ReplaceWordsSolver() { delete root; }

    string replaceWords(vector<string>& roots, string sentence) {
        for (const string& r : roots) insert(r);

        stringstream ss(sentence);
        string word, result;
        bool first = true;
        while (ss >> word) {
            if (!first) result += ' ';
            result += findRoot(word);
            first = false;
        }
        return result;
    }
};

int main() {
    // Problem 1: Longest Word in Dictionary
    {
        vector<string> words = {"w", "wo", "wor", "worl", "world"};
        LongestWordSolver solver;
        cout << "Longest Word in Dictionary: \"" << solver.longestWord(words) << "\"" << endl;
        // Expected: "world"
    }
    {
        vector<string> words = {"a", "banana", "app", "appl", "ap", "apply", "apple"};
        LongestWordSolver solver;
        cout << "Longest Word in Dictionary: \"" << solver.longestWord(words) << "\"" << endl;
        // Expected: "apple"
    }

    // Problem 2: Replace Words
    {
        vector<string> roots = {"cat", "bat", "rat"};
        string sentence = "the cattle was rattled by the battery";
        ReplaceWordsSolver solver;
        cout << "Replace Words: \"" << solver.replaceWords(roots, sentence) << "\"" << endl;
        // Expected: "the cat was rat by the bat"
    }
    {
        vector<string> roots = {"a", "b", "c"};
        string sentence = "aadsfasf absfasf acasdf";
        ReplaceWordsSolver solver;
        cout << "Replace Words: \"" << solver.replaceWords(roots, sentence) << "\"" << endl;
        // Expected: "a a a"
    }

    return 0;
}
