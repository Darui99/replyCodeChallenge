#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <string>
#include <bitset>
#include <ctime>
#include <random>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <random>
#pragma comment(linker, "/STACK:256000000")

using namespace std;

typedef long long ll;

const int INF = (int)1e9;
const ll LINF = (ll)1e18;

struct edge {
	ll f, cap;
	int from, to;

	edge(int u, int v, int e_cap) {
		from = u;
		to = v;
		cap = e_cap;
		f = 0;
	}
};

vector <edge> e;
vector <vector <int>> gr;
vector <vector <int>> gr_rev;
vector <int> dist, ptr;
ll ans = 0;

void bfs(int s) {
	dist.assign(gr.size(), INF);
	queue <int> q;
	q.push(s);
	vector <bool> used(gr.size(), false);
	dist[s] = 0;
	used[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto i : gr[v]) {
			if (!used[e[i].to] && e[i].cap - e[i].f > 0) {
				used[e[i].to] = true;
				dist[e[i].to] = dist[v] + 1;
				q.push(e[i].to);
			}
		}
	}
}

ll dfs(int v, ll d, int t) {
	if (v == t) {
		return d;
	}
	for (int i = ptr[v]; i < (int)gr[v].size(); i++) {
		int id = gr[v][i];
		if (e[id].f == e[id].cap || dist[v] + 1 != dist[e[id].to]) {
			ptr[v]++;
			continue;
		}
		ll cur = dfs(e[id].to, min(d, e[id].cap - e[id].f), t);
		if (cur > 0) {
			e[id].f += cur;
			e[id ^ 1].f -= cur;
			return cur;
		}
		ptr[v]++;
	}
	return 0;
}

void flow(int s, int t) {
	ans = 0;
	while (true) {
		ptr.assign(gr.size(), 0);
		bfs(s);
		if (dist[t] == INF) {
			return;
		}
		while (true) {
			ll cur = dfs(s, LINF, t);
			if (cur == 0) {
				break;
			}
			ans += cur;
		}
	}
}

void add_edge(int u, int v, int c) {
	edge e1(u, v, c);
	edge e2(v, u, 0);
	gr[u].push_back(e.size());
	gr_rev[v].push_back(e.size());
	e.push_back(e1);
	gr[v].push_back(e.size());
	gr_rev[u].push_back(e.size());
	e.push_back(e2);
}

int n, m;

int get_v(int x, int y, int z, int in) { //0 == in, 1 == out
	return ((x * m + y) * 2 + z) * 2 + in;
}

vector <char> used_s, used_t;

void dfs_s(int v) {
	used_s[v] = true;
	for (int edge : gr[v]) {
		if (!used_s[e[edge].to] && e[edge].cap > 0 && e[edge].f < e[edge].cap) {
			dfs_s(e[edge].to);
		}
	}
}

void dfs_t(int v, int dp = 0) {
	used_t[v] = true;
	for (int edge : gr_rev[v]) {
	
		if (!used_t[e[edge].from] && e[edge].cap > 0 && e[edge].f < e[edge].cap) {
			dfs_t(e[edge].from, dp + 1);
		}
	}
}

void shuffle() {
	for (auto v : gr) {
		shuffle(v.begin(), v.end(), mt19937(random_device()()));
	}
}

void solve(int test) {
	cerr << "test = " << test << '\n';
	e.clear();
	gr.clear();
	gr_rev.clear();
	ans = 0;

	cin >> n >> m;
	char c;
	vector<vector<vector<int> > > a(n, vector<vector<int> >(m, vector<int>(2)));
	int sx, sy, sz, tx, ty, tz;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < 2; k++) {
				cin >> c;
				int cap = INF;
				if (c == 'S') {
					sx = i; sy = j; sz = k;
				}
				else if (c == 'D') {
					tx = i; ty = j; tz = k;
				}
				else {
					cap = c - '0';
				}
				a[i][j][k] = cap;
			}
		}
	}
	int v = n * m * 4;
	gr.resize(v);
	gr_rev.resize(v);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < 2; k++) {
				if ((i + j) % 2 == 0) {
					if (i != 0) {
						add_edge(get_v(i, j, k, 1), get_v(i - 1, j, 1, 0), INF);
					}
					if (i != n - 1) {
						add_edge(get_v(i, j, k, 1), get_v(i + 1, j, 0, 0), INF);
					}
					if (k == 0) {
						if (j != 0) {
							add_edge(get_v(i, j, k, 1), get_v(i, j - 1, 0, 0), INF);
							add_edge(get_v(i, j, k, 1), get_v(i, j - 1, 1, 0), INF);
						}
					}
					else {
						if (j != m - 1) {
							add_edge(get_v(i, j, k, 1), get_v(i, j + 1, 0, 0), INF);
							add_edge(get_v(i, j, k, 1), get_v(i, j + 1, 1, 0), INF);
						}
					}
				}
				else {
					if (j != 0) {
						add_edge(get_v(i, j, k, 1), get_v(i, j - 1, 1, 0), INF);
					}
					if (j != m - 1) {
						add_edge(get_v(i, j, k, 1), get_v(i, j + 1, 0, 0), INF);
					}
					if (k == 0) {
						if (i != 0) {
							add_edge(get_v(i, j, k, 1), get_v(i - 1, j, 0, 0), INF);
							add_edge(get_v(i, j, k, 1), get_v(i - 1, j, 1, 0), INF);
						}
					}
					else {
						if (i != n - 1) {
							add_edge(get_v(i, j, k, 1), get_v(i + 1, j, 0, 0), INF);
							add_edge(get_v(i, j, k, 1), get_v(i + 1, j, 1, 0), INF);
						}
					}
				}
				add_edge(get_v(i, j, k, 1), get_v(i, j, 1 - k, 0), INF);
				add_edge(get_v(i, j, k, 0), get_v(i, j, k, 1), a[i][j][k]);
			}
		}
	}
	cerr << "HERE\n";
	int s = get_v(sx, sy, sz, 1);
	int t = get_v(tx, ty, tz, 0);
	//shuffle();
	flow(s, t);
	used_s.assign(v, false);
	used_t.assign(v, false);
	dfs_s(s);
	cerr << "dfs s\n";
	dfs_t(t);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < 2; k++) {
				int in = get_v(i, j, k, 0), out = get_v(i, j, k, 1);
				if (used_s[in] && !used_s[out] && used_t[out] && !used_t[in]) {
					if (a[i][j][k] < 9) {
						cout << "Case #" << test << ": " << i << " " << j << " " << k << "\n";
						return;
					}
				}
			}
		}
	}
	cout << "Case #" << test << ": -1\n";
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		solve(i + 1);
	}
	return 0;
}