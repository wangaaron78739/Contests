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

template <class C, bool directed>
struct Dijkstra {
    template <class T>
    using pqg = priority_queue<T, vector<T>, greater<T>>;
    int n;
    vector<C> dist;
    vector<vector<pair<int, C>>> adj;
    void init(int _n) {
        n = _n;
        adj.clear();
        adj.resize(n);
    }
    void add_edge(int u, int v, C cost) {
        adj[u].push_back({v, cost});
        if (!directed) adj[v].push_back({u, cost});
    }
    C compute(int st, int de = -1) {
        dist.assign(n, numeric_limits<C>::max());
        using T = pair<C, int>;
        pqg<T> pq;
        auto add = [&](int a, C b) {
            if (dist[a] <= b) return;
            pq.push({dist[a] = b, a});
        };
        add(st, 0);
        while ((int)pq.size()) {
            T x = pq.top();
            if (de != -1 && x.first == de) {
                return dist[de];
            }
            pq.pop();
            if (dist[x.second] < x.first) continue;
            for (auto &y : adj[x.second]) {
                add(y.first, x.first + y.second);
            }
        }
        return C{};
    }
};

struct edge {
    int u, v;
};

int main() {
    ios::sync_with_stdio(false);
#ifndef AARON_DEBUG
    cin.tie(nullptr);
#endif
    int I, S, L, U;
    cin >> I >> S >> L >> U;
    Dijkstra<int, false> dj;
    dj.init(I);
    vector<edge> streets;
    for (size_t i = 0; i < S; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dj.add_edge(u, v, w);
        streets.push_back({u, v});
    }
    dj.compute(0);
    int max = (U - 1) / 2;
    int ans = 0;
    for (int i = 0; i < S; i++) {
        if (dj.dist[streets[i].u] <= max || dj.dist[streets[i].v] <= max) {
            ans++;
        }
    }
    cout << ans << endl;
}
