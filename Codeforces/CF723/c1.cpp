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

int main() {
    ios::sync_with_stdio(false);
#ifndef AARON_DEBUG
    cin.tie(nullptr);
#endif

    ll n;
    cin >> n;
    vector<ll> a(n);
    vector<vector<ll>> dp(n, vector<ll>(n + 1, -1));
    for (auto &x : a) cin >> x;
    dp[0][0] = 0;
    if (a[0] >= 0) dp[0][1] = a[0];
    for (ll i = 1; i < n; i++) {
        auto next = dp[i - 1];
        for (ll j = 0; j < n; j++) {
            if (dp[i - 1][j] != -1 && dp[i - 1][j] + a[i] >= 0)
                next[j + 1] = max(dp[i - 1][j] + a[i], next[j + 1]);
        }
        dbg(next);
        dp[i] = next;
    }
    ll ans = 0;
    for (ll i = 0; i <= n; i++) {
        if (dp.back()[i] >= 0) ans = max(ans, i);
    }
    cout << ans << endl;
}
