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

const int maxN = 3e5;
vector<int> ken_adj[maxN], sor_adj[maxN];
int st[maxN], et[maxN];
set<pair<int, int>> S;
int ans = 0;

void dfs1(int u, int &time) {
    st[u] = time++;
    for (int v : ken_adj[u]) dfs1(v, time);
    et[u] = time++;
}

int comp(int u) { return -1; }

void dfs2(int u) {
    add(u);
    if (sor_adj[u].empty()) ans = max(ans, (int)S.size());
    for (int v : sor_adj[u]) dsf2(v);
}

void run_case() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ken_adj[i].clear();
        sor_adj[i].clear();
        st[i] = et[i] = 0;
    }
    S.clear();
    ans = 0;
    for (int v = 0; v < n - 1; v++) {
        int u;
        cin >> u;
        u--;
        sor_adj[u].push_back(v);
    }
    for (int v = 0; v < n - 1; v++) {
        int u;
        cin >> u;
        u--;
        ken_adj[u].push_back(v);
    }
    int time = 0;
    dfs1(0, time);
    assert(time == 2 * n);
    dfs2(0);
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
