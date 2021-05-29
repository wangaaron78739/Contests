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

struct point {
    double x, y;
};

double dist(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

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
    }
};

vector<point> p;
double x, y;
bool binsearch(double dist) { return true; }

int main() {
    ios::sync_with_stdio(false);
#ifndef AARON_DEBUG
    cin.tie(nullptr);
#endif
    cin >> x >> y;
    cin >> n;
    for (int i = 0; i < n; i++) {
        double a, b;
        cin >> a >> b;
        p.push_back({a, b});
    }
    const int n = p.size();
    Dijkstra<double, false> dij(n + 2);
    int u = n, v = n + 1;
    for (int i = 0; i < n; i++) {
        dij.add_edge(i, u, min(y - p[i].y, p[i].x));
        dij.add_edge(i, v, min(x - p[i].x, p[i].y));
        for (int j = 0; j < n; j++) {
            dij.add_edge(i, j, dist(p[i], p[j]) / 2);
        }
    }

    dij.compute(u, v);
    int u = n, v = n + 1;
    while (hi - lo > 1e-6) {
        double mid = (hi + lo) / 2;
        if (binsearch(mid, p)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    cout << mid << endl;
}
