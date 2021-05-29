// Fenwick Tree
// Computes partial sums a[0] + a[1] + ... + a[pos - 1]
// updates single elements a[i] using difference of old and new
// Time: O(log n)
template <typename T>
struct Fenwick {
    std::vector<T> s;
    int n;

    Fenwick(int _n) : n(_n) { s.resize(n); }

    // a[pos] += dif
    inline void update(int pos, T dif) {
        for (; pos < n; pos |= pos + 1) s[pos] += dif;
    }

    // sum of values in [0, pos)
    inline T query(int pos) {
        T res{};
        for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
        return res;
    }

    // min pos s.t. sum of [0, pos] >= sum
    // Returns n if no sum is >= sum or -1 if empty set is.
    inline int lower_bound(T sum) {
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw <= n && s[pos + pw - 1] < sum)
                pos += pw, sum -= s[pos - 1];
        }
        return pos;
    }
};
