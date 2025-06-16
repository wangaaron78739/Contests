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
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> freq;
    for (auto &x : a) {
        cin >> x;
        freq[x]++;
    }
    vector<int> can(n);
    for (int i = 0; i < n; i++) {
        can[i] = freq[a[i]] == 1;
    }
    int score = n - freq.size();

    // remove duplicate bad, remove single ok
    int i = 0;
    int has = 0;
    int best_i = 0, best_j = 0;
    for (int j = 0; j < n; j++) {
        if (can[j]) {
            if (best_j - best_i + 1 <= j - i + 1) {
                best_i = i;
                best_j = j;
                has = 1;
            }
        } else {
            i = j + 1;
        }
    }
    if (has || n == 1) {
        cout << best_i + 1 << " " << best_j + 1 << endl;
    } else {
        cout << 0 << endl;
    }
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
