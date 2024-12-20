#include <bits/stdc++.h>
using namespace std;
namespace rv = std::ranges::views;
using i64 = std::int64_t;
#define F first
#define S second

using vertex_t = pair<int, int>;

map<vertex_t, int> dijkstra(vector<string>& grid, vertex_t& startv) {
    map<vertex_t, int> dist;
    auto cmp = [&dist](vertex_t l, vertex_t m) { return dist[l] > dist[m];};
    priority_queue<vertex_t, vector<vertex_t>, decltype(cmp)>
        priority_queue(cmp);
    dist[startv] = 0;
    priority_queue.push(startv);
    set<vertex_t> seen;
    int m{(int)grid.size()}, n{(int)grid[0].size()};
    auto in_range = [m, n](vertex_t& p) { return p.F >= 0 && p.F < m && p.S >= 0 && p.S < n; };

    while (!priority_queue.empty()) {
        auto vertex = priority_queue.top();
        priority_queue.pop();
        seen.insert(vertex);
        for (int i{}, j=1, count{}; count < 4; count++, tie(i, j) = tuple{j, -i}) {
            vertex_t nbr{vertex.F + i, vertex.S + j};
            if (in_range(nbr) && !seen.contains(nbr) && grid[nbr.F][nbr.S] != '#') {
                auto newdist = dist[vertex] + 1;
                if (!dist.contains(nbr) || dist[nbr] > newdist) {
                    dist[nbr] = newdist;
                    priority_queue.push(nbr);
                }
            }
        }

    }
    return dist;
}

int main() {
    freopen("./20.txt", "r", stdin);
    vector<string> grid;
    for (string line; cin >> line; )
        grid.push_back(line);
    vertex_t startv, endv;
    int m{(int)grid.size()}, n{(int)grid[0].size()};
    for (auto [i, j] : rv::cartesian_product(rv::iota(0, m), rv::iota(0, n))) {
        if (grid[i][j] == 'S') startv = vertex_t{i, j};
        if (grid[i][j] == 'E') endv = vertex_t{i, j};
    }

    auto dist_start = dijkstra(grid, startv);
    auto dist_end = dijkstra(grid, endv);

    auto cheat = [m, n](vertex_t v, int lvl) {
        set<vertex_t> set;
        auto in_range = [m, n](vertex_t& p) { return p.F >= 0 && p.F < m && p.S >= 0 && p.S < n; };
        for (int i = lvl, j = 0; i > 0; i--, j++) {
            for (int ni = i, nj = j, cnt = 0; cnt < 4; cnt++, tie(ni, nj) = tuple{nj, -ni}) {
                auto nbr = vertex_t{v.F + ni, v.S + nj};
                if (in_range(nbr)) set.insert(nbr);
            }
        }
        return set;
    };

    auto reduction_count = [&dist_start, &dist_end, &cheat, &endv, m, n](int level) {
        i64 count{};
        for (auto [i, j] : rv::cartesian_product(rv::iota(0, m), rv::iota(0, n))) {
            vertex_t v{i, j};
            if (dist_start.contains(vertex_t{i, j})) {
                for (int lvl = 2; lvl <= level; lvl++) {
                    auto dist = dist_start[v] + lvl;
                    for (const auto& nbr : cheat(v, lvl)) {
                        if (dist_end.contains(nbr)) {
                            dist += dist_end[nbr];
                            if (dist_start[endv] - dist >= 100)
                                count++;
                            dist -= dist_end[nbr];
                        }
                    }
                }
            }
        }
        return count;
    };
    cout << reduction_count(2) << endl;
    cout << reduction_count(20) << endl;
}
