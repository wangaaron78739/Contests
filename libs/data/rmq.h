// Range Minimum Queries on an array
// Returns min(V[a], V[a + 1], ... V[b - 1]) in constant time.
// Usage:
//  RMQ rmq(values);
//  rmq.query(inclusive, exclusive);
// Time: $O(|V| \log |V| + Q)$
#include <cassert>
#include <vector>
template <class T>
struct RMQ {
    T f(T a, T b) { return std::min(a, b); }
    std::vector<std::vector<T>> jmp;

    RMQ(const std::vector<T>& V) {
        int N = (int)V.size(), on = 1, depth = 1;
        while (on < N) on *= 2, depth++;
        jmp.assign(depth, V);
        for (int i = 0; i < depth - 1; i++)
            for (int j = 0; j < N; j++) {
                int width = 1 << i;
                jmp[i + 1][j] =
                    f(jmp[i][j], jmp[i][std::min(N - 1, j + width)]);
            }
    }

    inline T query(int a, int b) {
        assert(a < b);  // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return f(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};
#undef op
