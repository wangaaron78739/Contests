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

typedef long long ll;
vector<vector<ll>> adj;
vector<ll> l, r;
vector<array<ll, 2>> dp;
vector<ll> visited;

void dfs(ll u) {
    if (visited[u]) return;
    visited[u] = 1;
    for (auto v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
            dp[u][0] +=
                max(dp[v][0] + abs(l[v] - l[u]), dp[v][1] + abs(r[v] - l[u]));
            dp[u][1] +=
                max(dp[v][0] + abs(l[v] - r[u]), dp[v][1] + abs(r[v] - r[u]));
        }
    }
}

void run_case() {
    ll n;
    cin >> n;
    l = vector<ll>(n);
    r = vector<ll>(n);
    visited.assign(n, 0);
    adj.assign(n, {});
    dp.assign(n, {0, 0});
    for (ll i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }
    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0);
    cout << max(dp[0][0], dp[0][1]) << endl;
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
