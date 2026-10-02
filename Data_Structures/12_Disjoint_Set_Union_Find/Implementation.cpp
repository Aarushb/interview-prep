/*
PROBLEM: Disjoint Set Union / Union-Find — Custom Implementation
DESCRIPTION: Implement a DSU from scratch, supporting find (with path compression) and
unite/union (by rank), plus a helper to check if two elements are connected and to count the
number of disjoint sets currently remaining.
CONSTRAINTS: General-purpose implementation over a fixed universe of n elements, indexed 0..n-1.
Operations should be correct for arbitrary sequences of unite/find/connected calls.
EXAMPLE INPUT/OUTPUT: See main() below for a runnable usage demo.
*/

/*
APPROACH:
Two parallel arrays represent the forest of sets: `parent[i]` points to i's parent (a root points
to itself), and `rank[i]` is an upper bound on the height of the subtree rooted at i (used only to
decide how to union, never as an exact height after path compression).

find(x): walk parent pointers until reaching a node that is its own parent (the root). This is
PATH COMPRESSION: rather than just returning the root, we re-point x directly to it (and, in this
recursive implementation, every node visited along the way also gets re-pointed to the root, since
each call assigns `parent[x] = find(parent[x])`). This means the *next* find on any of those nodes
is O(1) — the tree gets flattened as a side effect of querying it, so trees never stay deep for
long even under adversarial union sequences.

unite(x, y): find both roots. If they're already the same, x and y are already connected — no-op.
Otherwise we must link one root under the other, and UNION BY RANK decides which way: attach the
root with the smaller rank underneath the root with the larger rank. This keeps the resulting tree
no taller than before (a short tree merged under a tall one doesn't increase the tall one's
height), preventing the worst case of always attaching a big tree under a small one and building a
long chain. If both roots have equal rank, we pick either as the new root and increment its rank by
one (this is the only case where the tree's height can grow, and even then only by 1). We also
decrement a `numSets` counter whenever a successful union merges two previously-separate sets.

Combined, path compression + union by rank give near O(1) amortized find/unite: this bound is
formally O(alpha(n)), the inverse Ackermann function, which is <= 4 for any n up to (and vastly
beyond) the number of atoms in the observable universe — practically constant time.

connected(x, y) is just find(x) == find(y). countSets() returns the maintained numSets counter,
avoiding an O(n) scan.
*/

#include <bits/stdc++.h>
using namespace std;

class DisjointSetUnion {
private:
    vector<int> parent;
    vector<int> rank_;
    int numSets;

public:
    explicit DisjointSetUnion(int n) : parent(n), rank_(n, 0), numSets(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    // Finds the representative (root) of x's set, compressing the path along the way.
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // path compression
        }
        return parent[x];
    }

    // Unites the sets containing x and y. Returns true if they were previously separate.
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false; // already in the same set

        // Union by rank: attach the shorter tree under the taller tree's root.
        if (rank_[rootX] < rank_[rootY]) {
            parent[rootX] = rootY;
        } else if (rank_[rootX] > rank_[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank_[rootX]++;
        }

        numSets--;
        return true;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    int countSets() const {
        return numSets;
    }
};

int main() {
    DisjointSetUnion dsu(10); // elements 0..9, all in their own set initially

    cout << "Initial set count: " << dsu.countSets() << endl; // 10

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    dsu.unite(5, 6);
    dsu.unite(6, 7);
    dsu.unite(7, 8);

    cout << boolalpha;
    cout << "connected(0, 2): " << dsu.connected(0, 2) << endl; // true (0-1-2 merged)
    cout << "connected(0, 3): " << dsu.connected(0, 3) << endl; // false
    cout << "connected(5, 8): " << dsu.connected(5, 8) << endl; // true (5-6-7-8 merged)
    cout << "connected(9, 0): " << dsu.connected(9, 0) << endl; // false (9 untouched)

    cout << "Set count after unions: " << dsu.countSets() << endl; // 10 - 6 successful unions = 4

    dsu.unite(0, 3); // merges {0,1,2} with {3,4}
    cout << "connected(2, 4) after merging: " << dsu.connected(2, 4) << endl; // true
    cout << "Set count after merging: " << dsu.countSets() << endl; // 3

    return 0;
}
