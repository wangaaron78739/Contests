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

int main() {
    ios::sync_with_stdio(false);
#ifndef AARON_DEBUG
    cin.tie(nullptr);
#endif
    int n, k;
    cin >> n >> k;
    unordered_map<string, int> mp, occur;

    for (int i = 0; i < 3 * n + 1; i++) {
        string s;
        getline(cin, s);
        if (s.size() == 0) continue;
        mp[s]++;
        occur[s] = i;
    }
    vector<pair<string, int>> v(mp.begin(), mp.end());
    dbg(v);
    dbg(occur);
    sort(v.begin(), v.end(), [&](auto a, auto b) {
        if (a.second > b.second) return true;
        if (a.second < b.second) return false;
        return occur[a.first] > occur[b.first];
    });
    for (int i = 0; i < min(k, (int)v.size()); i++) {
        cout << v[i].first << endl;
    }
}
