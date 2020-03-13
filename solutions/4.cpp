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
#pragma comment(linker, "/STACK:256000000")
using namespace std;

#define in(s) freopen(s, "r", stdin)
#define out(s) freopen(s, "w", stdout)
#define forn(i, n) for (int i = 0; i < n; i++)
#define endl '\n'
#define mp make_pair

typedef long long ll;
typedef long double ld;

const int alph = 26;
const int inf = (int)1e+9 + 7;

/*

struct Node {
	int next[alph];
	bool term;

	Node() {
		for (int i = 0; i < alph; i++)
			next[i] = -1;
		term = false;
	}
};

vector <Node> trie;

inline void add(const string &s) {
	int v = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		int c = (int)(s[i] - 'a');
		if (trie[v].next[c] == -1) {
			trie[v].next[c] = (int)trie.size();
			trie.emplace_back();
		}
		v = trie[v].next[c];
	}
	trie[v].term = true;
}

inline void solve(int T) {
	trie.clear();
	trie.emplace_back();

	int n;
	cin >> n;
	string s, x;
	cin >> s;

	for (int i = 0; i < n; i++) {
		cin >> x;
		for (int j = 0; j < (int)x.size(); j++)
			add(x.substr(j, (int)x.size() - j));
	}

	n = (int)s.size();
	vector <int> dp(s.size() + 1, inf);
	dp.back() = 0;
	for (int i = n - 1; i >= 0; i--) {
		int v = 0, c;
		for (int j = i; j < n; j++) {
			c = (int)(s[j] - 'a');
			if (trie[v].next[c] != -1) {
				v = trie[v].next[c];
			}
			else {
				break;
			}
			if (trie[v].term) {
				if (dp[i] > dp[j + 1] + 1)
					dp[i] = min(dp[i], dp[j + 1] + 1);
			}
		}
	}
	if (dp[0] == inf)
		dp[0] = -1;
	cout << "Case #" << T << ": " << dp[0] << endl;
	//cout << dp[0] << endl;
}

*/

vector <int> build_z(const string &s) {
	int n = (int)s.size();
	vector <int> z(n);

	for (int i = 1, l = 0, r = 0; i < n; i++) {
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			z[i]++;
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	return z;
}

inline void solve(int T) {
	int n, l;
	cin >> n;
	string s, x;
	cin >> s;
	l = (int)s.size();

	vector <int> maxu(l);

	for (int i = 0; i < n; i++) {
		cin >> x;
		string cur = s + "$" + x;
		reverse(cur.begin(), cur.end());
		vector<int> kek = build_z(cur);
		for (int j = (int)x.size() + 1; j < (int)kek.size(); j++) {
			if (kek[j] == 0)
				continue;
			int to = l - 1 - (j + kek[j] - 1 - (int)x.size() - 1);
			maxu[to] = max(maxu[to], kek[j]);
		}
	}

	vector <int> dp(l + 1, inf);
	dp.back() = 0;

	for (int i = l - 1; i >= 0; i--) {
		for (int j = i; j < i + maxu[i]; j++) {
			if (dp[i] > dp[j + 1] + 1) {
				dp[i] = dp[j + 1] + 1;
			}
		}
	}

	if (dp[0] == inf)
		dp[0] = -1;
	cout << "Case #" << T << ": " << dp[0] << endl;
}

int main()
{
	in("input.txt");
	out("output.txt");
	srand(1373737);
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for (int i = 1; i <= t; i++)
		solve(i);

	return 0;
}