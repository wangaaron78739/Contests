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

void run_case() {
	int64_t n, k;
	cin >> n >> k;
	vector<int64_t> v(n);
	for (auto &x : v) cin >> x;

	int total = v[0];
	int needed = 0;

	for (int i = 1; i < n; i++) {
		auto x = v[i];

		needed += max(0LL, (100 * x - k * total);
		total += max(0LL, 100 * x - k * total) + x;
	}
	cout << needed << endl;
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