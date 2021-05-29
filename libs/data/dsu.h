// Disjoint-set
// Time: O(\alpha(N))
#include <vector>
struct DSU {
    std::vector<int> e;
    int n;

    DSU(int _n) : n(_n), e(_n, -1) {}
    inline bool same_set(int a, int b) { return find(a) == find(b); }
    inline int size(int x) { return -e[find(x)]; }
    inline int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    inline void join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (e[a] > e[b]) std::swap(a, b);
        e[a] += e[b];
        e[b] = a;
    }
};
