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

int64_t fact(int n) {
	int64_t x = 1;
	for (int i = 1; i <= n; i++) {
		x *= i;
		x %= MOD;
	}
	return x;
}

void run_case() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a) cin >> x;
	int t = a[0];
	int zc = 0;
	for (auto x : a) {
		t &= x;
	}
	for (auto x : a) {
		if (x == t) zc++;
	}
	if (zc < 2) {
		cout << "0\n";
		return;
	}
	int64_t m = fact(n - 2);
	dbg(m);
	m *= zc;
	m %= MOD;
	m *= (zc - 1);
	m %= MOD;
	cout << m << "\n";
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
