#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second

bool is_anti_node(const pair<int, int>& p, map<char, vector<pair<int, int>>>& map);

int main() {
    freopen("./8.txt", "r", stdin);
    // freopen("./tmp.txt", "r", stdin);
    vector<string> grid;
    for (string line; getline(cin, line); ) {
        grid.push_back(line);
    }
    int m = (int)grid.size(), n = (int)grid[0].size();
    map<char, vector<pair<int, int>>> map;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            auto c = grid[i][j];
            if (c != '.') {
                if (!map.contains(c)) {
                    map[c] = vector<pair<int, int>>();
                }
                map[c].push_back(make_pair(i, j));
            }
        }
    }

    auto in_grid = [m, n](pair<int, int> v) { return v.F >= 0 && v.F < m && v.S >= 0 && v.S < n; };
    auto plus = [](pair<int, int> v1, pair<int, int> v2) { return make_pair(v1.F + v2.F, v1.S + v2.S); };
    auto minus = [](pair<int, int> v1, pair<int, int> v2) { return make_pair(v1.F - v2.F, v1.S - v2.S); };
    auto mult = [](pair<int, int> v1, int n) { return make_pair(v1.F * n, v1.S * n); };

    set<pair<int, int>> set;
    for (const auto& [key, value] : map) {
        for (auto it1 = value.begin(); it1 != value.end(); it1++) {
            for (auto it2 = it1 + 1; it2 != value.end(); it2++) {
                auto v1 = *it1, v2 = *it2;
                if (v1 == v2) continue;
                auto an = plus(v1, mult(minus(v2, v1), 2));
                if (in_grid(an)) {
                    set.insert(an);
                }
                an = plus(v2, mult(minus(v1, v2), 2));
                if (in_grid(an)) {
                    set.insert(an);
                }
            }
        }
    }
    cout << set.size() << endl;

    set.clear();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            auto p = make_pair(i, j);
            if (is_anti_node(p, map)) set.insert(p);
        }
    }
    cout << set.size() << endl;
}

bool is_anti_node(const pair<int, int>& p, map<char, vector<pair<int, int>>>& map) {
    for (const auto& [key, value] : map) {
        for (auto it1 = value.begin(); it1 != value.end(); it1++) {
            for (auto it2 = it1 + 1; it2 != value.end(); it2++) {
                auto v1 = *it1, v2 = *it2;
                if (p == v1 || p == v2)
                    return true;
                else {  // is point on line
                    if ((p.F - v1.F) * (v2.S - v1.S) == (p.S - v1.S) * (v2.F - v1.F))
                        return true;
                }
            }
        }
    }
    return false;
}
