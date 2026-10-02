# Trie (Prefix Tree)

## Overview
A trie is a tree in which each edge is labeled with a character, and each path from the root spells out a string. Every node holds an array (or map) of children — one slot per possible next character — plus a boolean flag marking whether the path from the root to that node forms a complete, previously-inserted word. Common words share their prefix's nodes, so the trie stores a whole dictionary of overlapping prefixes without duplicating the shared parts.

## Operations & Complexity
| Operation | Time | Space |
|---|---|---|
| insert(word) | O(L) | O(L) new nodes worst case |
| search(word) | O(L) | O(1) |
| startsWith(prefix) | O(L) | O(1) |
| overall storage (N words, avg length L) | — | O(N * L) worst case, less with shared prefixes |

L = length of the word/prefix being processed. Children lookup is O(1) with a fixed-size array (e.g. 26 for lowercase letters) or O(1) average with a hash map.

## When It's Used in Interviews
- Autocomplete / typeahead suggestion systems (find all words with a given prefix).
- Spell checkers and dictionary lookups.
- Problems that repeatedly test "does any word start with X" faster than scanning a word list each time.
- IP routing (longest prefix match) and word-search-on-a-board style problems where you need to prune search early based on partial matches.
- Any problem framed around prefixes, word roots, or dictionaries where a hash set of full words isn't enough because you need partial-match queries.

## Trade-offs
- vs hash set of words: a hash set answers "is this exact word present" in O(L) but cannot efficiently answer "does any word start with this prefix" — that requires O(N*L) scanning. A trie answers both in O(L).
- vs sorted array + binary search: binary search gives O(L log N) prefix range-finding; a trie gives O(L) but uses more memory (one node per character, not per word).
- Memory overhead: array-based children (e.g. 26 pointers per node) can waste space for sparse alphabets; a hash-map-based trie trades some speed for lower memory when the character set is large or sparse.
