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
