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

void run_case() {
    int n, m;
    cin >> n >> m;
    string s;
    vector<int> a(n), b(n);
    cin >> s;
    for (int j = 0; j < min(n, m); j++) {
        string _s = s;
        for (int i = 0; i < n; i++) {
            int neigh = 0;
            if (i) neigh += s[i - 1] == '1';
            if (i != n - 1) neigh += s[i + 1] == '1';
            if (s[i] == '0' && neigh == 1) _s[i] = '1';
        }
        s = _s;
    }
    cout << s << endl;
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
