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

typedef long long ll;

void solve() {
    string s;
    cin >> s;
    string C = "ANTO";
    sort(C.begin(), C.end());
    string ans = "";
    ll best_score = -1;
    do {
        string curr = s;
        ll score = 0;
        string res = "";
        for (char c : C) {
            ll inv = 0;
            string z = "";
            for (char x : curr) {
                if (x == c) {
                    score += inv;
                    res += x;
                } else {
                    inv++;
                    z += x;
                }
            }
            curr = z;
        }
        if (score > best_score) {
            best_score = score;
            ans = res;
        }
    } while (next_permutation(C.begin(), C.end()));
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
#ifndef AARON_DEBUG
    cin.tie(nullptr);
#endif
    int t;
    cin >> t;
    while (t--) solve();
}
