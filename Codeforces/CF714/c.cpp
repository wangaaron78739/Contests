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
template <typename T_container,
		  typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
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

const int64_t MOD = 1e9 + 7;

void run_case() {
	string n;
	int m;
	cin >> n >> m;
	array<int64_t, 10> freq = {};
	for (char c : n) {
		freq[c - '0']++;
	}
	int64_t ans = 0;
	while (m >= 10) {
		array<int64_t, 10> nfreq = {};
		for (int i = 0; i < 9; i++) {
			nfreq[i] += freq[i];
			nfreq[(i + 1) % 10] += freq[i];
		}
		nfreq[0] += freq[9];
		nfreq[1] += freq[9];
		nfreq[9] += freq[9];
		for (int i = 0; i < 10; i++) nfreq[i] %= MOD;
		freq = nfreq;
		m -= 10;
	}
	for (int i = 0; i < m; i++) {
		int z = 10 - i - 1;
		freq[z] *= 2;
		freq[z] %= MOD;
	}
	for (int64_t z : freq) ans += z;
	cout << ans << "\n";
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
