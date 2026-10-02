/*
PROBLEM: Add and Search Word (WordDictionary)
DESCRIPTION: Design a data structure supporting addWord(word) and search(pattern) where pattern may include '.' matching any letter.
CONSTRAINTS:
- 1 <= word.length, pattern.length <= 25; lowercase English letters and '.' in search
- At most 10^4 calls will be made to addWord and search.
EXAMPLE: add("bad"), add("dad"), add("mad"), search("pad") -> false, search(".ad") -> true, search("b..") -> true
*/

/*
APPROACH:
This is a standard trie with one twist: search patterns can contain '.' wildcards that must
match any single character. addWord is a normal trie insert; search is a DFS over the trie
where a literal character follows exactly one child edge, but a '.' fans out and recurses
into every non-null child at that level. The recursion only succeeds if it reaches the end
of the pattern on a node flagged as end-of-word.
*/

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    bool end = false;
    array<TrieNode*,26> next{};
    TrieNode(){ next.fill(nullptr); }
};

class WordDictionary {
public:
    WordDictionary(): root(new TrieNode()) {}
    ~WordDictionary(){ freeNode(root); }

    void addWord(const string& word){
        TrieNode* cur = root;
        for(char c: word){
            int i = c-'a';
            if(!cur->next[i]) cur->next[i] = new TrieNode();
            cur = cur->next[i];
        }
        cur->end = true;
    }

    bool search(const string& word){
        return dfs(word, 0, root);
    }

private:
    TrieNode* root;

    bool dfs(const string& w, int idx, TrieNode* node){
        if(!node) return false;
        if(idx == (int)w.size()) return node->end;
        char c = w[idx];
        if(c == '.'){
            for(TrieNode* nxt: node->next){
                if(nxt && dfs(w, idx+1, nxt)) return true;
            }
            return false;
        }
        return dfs(w, idx+1, node->next[c-'a']);
    }

    void freeNode(TrieNode* node){
        if(!node) return;
        for(auto* nxt: node->next) freeNode(nxt);
        delete node;
    }
};

int main(){
    WordDictionary dict;
    dict.addWord("bad");
    dict.addWord("dad");
    dict.addWord("mad");

    cout << boolalpha;
    cout << dict.search("pad") << "\n"; // false
    cout << dict.search(".ad") << "\n"; // true
    cout << dict.search("b..") << "\n"; // true
    cout << dict.search("b.d") << "\n"; // true
    cout << dict.search("ba") << "\n";  // false
    return 0;
}
