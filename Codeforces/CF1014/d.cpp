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

void run_case() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<char, int> freq;
    for (char c : s) freq[c]++;
    if (freq.size() == 1) {
        cout << "-1" << endl;
        return;
    }
    auto [_, min_value] =
        *min_element(freq.begin(), freq.end(),
                     [](auto a, auto b) { return a.second < b.second; });
    for (auto &[k, v] : freq) {
        v -= min_value;
    }
    int ans = 0;
    auto valid = [&]() {
        return freq['T'] == freq['I'] && freq['L'] == freq['T'];
    };
    auto third = [](char a, char b) -> char {
        for (char c : {'T', 'I', 'L'}) {
            if (c != a && c != b) {
                return c;
            }
        }
        std::abort();
    };
    for (int i = 0; i < n - 1; i++) {
        if (valid()) {
            cout << ans << endl;
            return;
        }
        int x = s[i];
        int y = s[i + 1];
        if (x == y) {
            continue;
        }
        char z = third(x, y);
        if (freq[z]) {
            freq[z]--;
        }
    }
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
