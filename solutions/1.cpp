#include <iostream>
#include <random>
#include <vector>
#include <map>

using namespace std;

namespace {
std::mutex cerr_m;

void tracei() {
}

template <typename T, typename... Ts>
void tracei(T const& t, Ts&&... ts) {
    cerr << t << "\n";
    tracei(std::forward<Ts>(ts)...);
}

template <typename T, typename... Ts>
void trace(T const& t, Ts&&... ts) {
    std::lock_guard<std::mutex> lg(cerr_m);
    tracei(t, std::forward<Ts>(ts)...);
}

int gen(int l, int r) {
    static mt19937 gen((int)time(nullptr));
    return uniform_int_distribution<int>(l, r)(gen);
}
}

int main() {
    int T, n, l, ts, team, prog, inp, ok;
    cin >> T;

    for (int tcase = 1; tcase <= T; ++tcase) {
        cin >> n >> l;

        vector<pair<int, map<int, int>>> teams(n);
        for (int i = 1; i <= n; ++i)
            teams[i - 1].first = i;

        for (int t = 0; t < l; ++t) {
            cin >> ts >> team >> prog >> inp >> ok;
            --team;

            if (!ok) continue;

            map<int, int>& sc = teams[team].second;
            int pid = prog * 10 + inp;
            auto it = sc.find(pid);

            if (it == sc.end() || it->second > ts) {
                sc[pid] = ts;
            }
        }

        vector<pair<int, int>> result(n);

        for (int t = 0; t < n; ++t) {
            for (auto p : teams[t].second) {
                result[t].first += (p.first % 10) * 100;
                result[t].second += p.second;
            }
        }

        sort(teams.begin(), teams.end(), [&result] (pair<int, map<int, int>> const& a, pair<int, map<int, int>> const& b) {
            if (result[a.first - 1].first != result[b.first - 1].first)
                return result[a.first - 1].first < result[b.first - 1].first;
            if (result[a.first - 1].second != result[b.first - 1].second)
                return result[a.first - 1].second > result[b.first - 1].second;
            return a.first > b.first;
        });

        cout << "Case #" << tcase << ": ";

        reverse(teams.begin(), teams.end());
        for (auto const& p : teams)
            cout << p.first << ' ';

        cout << "\n";
    }

    return 0;
}
