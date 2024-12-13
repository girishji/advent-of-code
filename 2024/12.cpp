#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
using plot_t = pair<char, bool>;
namespace rv = ranges::views;

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& p) {
    os << '(' << p.first << ", " << p.second << ')';
    return os;
}

int main() {
    freopen("./12.txt", "r", stdin);
    vector<vector<plot_t>> grid;
    auto make_plot = [](const char x) {return plot_t{x, false};};
    for (string line; getline(cin, line); ) {
        grid.push_back(line | views::transform(make_plot) | ranges::to<vector>());
    }
    int m = (int)grid.size(), n = (int)grid[0].size();

    auto inside = [&grid, m, n](int i, int j, char t) -> bool {
        return i >= 0 && i < m && j >= 0 && j < n && grid[i][j].F == t;
    };

    function<tuple<int, vector<pair<int, int>>>(int, int)> dfs =
        [&dfs, &grid, m, n](int i, int j) -> tuple<int, vector<pair<int, int>>> {
        int perim = 0;
        vector<pair<int, int>> plots{{{i, j}}};
        grid[i][j].S = true;
        auto inside =
            [&m, &n](int i, int j) { return i >= 0 && j >= 0 && i < m && j < n; };
        for (int row = 0, col = 1, cnt = 0; cnt < 4; cnt++, tie(row, col) = pair{col , -row}) {
            auto ni = i + row, nj = j + col;
            if (!inside(ni, nj) || grid[ni][nj].F != grid[i][j].F) {
                perim++;
            } else if (!grid[ni][nj].S) {
                auto [nperim, nplots] = dfs(ni, nj);
                perim += nperim;
                plots.insert(plots.end(), nplots.begin(), nplots.end());
            }
        }
        return {perim, plots};
    };

    auto sides = [&grid, m, n, &inside](vector<pair<int, int>>& plots) -> int {
        int sides{};
        set<pair<int, int>> set(plots.begin(), plots.end());
        for (int i = 0; i < m; i++) {
            vector active{false, false ,false};
            for (int j = 0; j < n; j++) {
                for (const auto& adj : {-1, 1}) {
                    if (!set.contains(pair{i, j}) || inside(i + adj, j, grid[i][j].F)) {
                        active[adj + 1] = false;
                    } else if (!active[adj + 1]) {
                        sides++;
                        active[adj + 1] = true;
                    }
                }
            }
        }
        for (int j = 0; j < n; j++) {
            vector active{false, false ,false};
            for (int i = 0; i < m; i++) {
                for (const auto& adj : {-1, 1}) {
                    if (!set.contains(pair{i, j}) || inside(i, j + adj, grid[i][j].F)) {
                        active[adj + 1] = false;
                    } else if (!active[adj + 1]) {
                        sides++;
                        active[adj + 1] = true;
                    }
                }
            }
        }
        return sides;
    };

    int price1 = 0, price2 = 0;
    for (auto [i, j] : views::cartesian_product(views::iota(0, m), views::iota(0, n))) {
        if (!grid[i][j].S) {
            auto [perim, plots] = dfs(i, j);
            int area = (int)plots.size();
            price1 += perim * area;
            price2 += sides(plots) * area;
        }
    }
    cout << price1 << " " << price2 << endl;
}
