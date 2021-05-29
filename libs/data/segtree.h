// Zero-indexed max-tree.
// Bounds are inclusive to the left and exclusive to the right.
// Can be changed by modifying T, LOW and f.
// Time: O(\log N)
#include <climits>
#include <vector>
struct SegTree {
    typedef int T;
    static const T LOW = INT_MIN;
    T f(T a, T b) { return std::max(a, b); }  // (any associative fn)
    std::vector<T> s;
    int n;
    SegTree(int n = 0, T def = 0) : s(2 * n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos > 1; pos /= 2)
            s[pos / 2] = f(s[pos & ~1], s[pos | 1]);
    }
    T query(int b, int e) {  // query [b, e)
        T ra = LOW, rb = LOW;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};
