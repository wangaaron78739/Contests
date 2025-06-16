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

void run_case() {
    int64_t n;
    cin >> n;
    vector<int64_t> a(n);
    int64_t sum = 0;
    for (auto &x : a) cin >> x;
    int64_t odd = 0, even = 0;
    int64_t best = 0;
    for (const auto &x : a) {
        if (x % 2 == 0)
            even++;
        else
            odd++;
        best = max(best, x);
        sum += x;
    }
    if (!even || !odd) {
        cout << best << endl;
        return;
    }
    cout << sum - odd + 1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
#ifndef AARON_DEBUG
    cin.tie(nullptr);
#endif

    int64_t tests;
    cin >> tests;

    while (tests-- > 0) run_case();
}
