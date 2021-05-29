#include <bits/stdc++.h>
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

const int MAX_N = 100000 + 5;
int n, m;
vector<int> adj[MAX_N];

vector<int> visited;
int bfs(int st) {
    visited.assign(n, 0);
    vector<pair<int, int>> q;
    auto add = [&](int v, int d) {
        if (!visited[v]) q.push_back({v, d});
        visited[v] = 1;
    };
    add(st, 0);
    int i = 0;
    while (i != (int)q.size()) {
        auto [u, dist] = q[i];
        for (int v : adj[u]) {
            add(v, dist + 1);
        }
        i++;
    }
    if (st == 0)
        for (int j = 0; j < n; j++) {
            if (!visited[j]) return -1;
        }
    return q.back().second;
}

int main() {
    ios::sync_with_stdio(false);
#ifndef AARON_DEBUG
    cin.tie(nullptr);
#endif
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int tp = bfs(i);
        if (tp == -1) {
            cout << -1 << endl;
            return 0;
        }
        ans = max(ans, tp);
    }
    cout << ans << endl;
}
