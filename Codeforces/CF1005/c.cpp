#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
using namespace std;

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
    os << '{';
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << '}';
}

void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}

#ifdef AARON_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

// a a a a b b b b b
// a a b a b b b b b

void run_case() {
    // Implement case here
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (auto &x : a) cin >> x;
    int64_t total = 0LL;
    int l = 0;
    int r = n - 1;
    while (l <= r && a[l] > 0) total += a[l++];
    while (l <= r && a[l] < 0) total += a[r--];
    while (l <= r) {
        int l2 = l;
        int r2 = r;
        int64_t total_l2 = 0;
        int64_t total_r2 = 0;
        while (l2 <= r2 && a[l2] < 0) total_l2 += a[l2++];
        while (l2 <= r2 && a[l2] > 0) total_r2 += a[r2--];
        if (total_) }
    cout << total << endl;
}

int main() {
    ios::sync_with_stdio(false);
#ifndef AARON_DEBUG
    cin.tie(nullptr);
#endif

    int tests;
    cin >> tests;

    while (tests-- > 0) run_case();
}
