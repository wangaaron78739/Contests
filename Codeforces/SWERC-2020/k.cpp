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
#include <string_view>
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

string s;
string_view sv;
string ans;

bool check(int size) {
    map<string_view, int> mp;
    for (int i = 0; i + size < s.size() + 1; i++) {
        dbg(string(sv.substr(i, size)));
        mp[sv.substr(i, size)]++;
    }
    for (int i = 0; i + size < s.size() + 1; i++) {
        int end = i + size;
        auto tmp = sv.substr(i, size);
        if (mp[tmp] == 1) {
            ans = string(tmp);
            dbg(ans);
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
#ifndef AARON_DEBUG
    cin.tie(nullptr);
#endif
    cin >> s;
    sv = string_view(s);
    for (int size = 1; size <= s.size(); size++) {
        unordered_map<string_view, int> mp;
        for (int i = 0; i + size <= s.size(); i++) {
            mp[sv.substr(i, size)]++;
        }
        for (int i = 0; i + size <= s.size(); i++) {
            if (mp[sv.substr(i, size)] == 1) {
                cout << string(sv.substr(i, size)) << endl;
                return 0;
            }
        }
    }
    assert(0);
}
