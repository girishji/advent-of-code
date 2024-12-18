#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second

pair<int, int> operator+(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

int main() {
    vector<string> maze;
    freopen("./16.txt", "r", stdin);
    for (string line; getline(cin, line); )
        maze.push_back(line);
    int m = (int)maze.size(), n = (int)maze[0].size();

    // Dijkstra
    using node_t = tuple<int, int, char>;
    map<node_t, int> cost;
    cost[tuple{m - 2, 1, '>'}] = 0;
    auto cmp = [&cost](node_t l, node_t m) { return cost[l] > cost[m];};
    priority_queue<node_t, vector<node_t>, decltype(cmp)> pque(cmp);
    pque.push(tuple{m - 2, 1, '>'});
    set<node_t> seen;
    map<node_t, vector<node_t>> pred;

    map<char, pair<int, int>> nxtloc{{'>', pair{0, 1}}, pair{'v', pair{1, 0}},
        pair{'<', pair{0, -1}}, pair{'^', pair{-1, 0}}};
    map<char, vector<char>> nxtdir{{'>', {'>', 'v', '^'}}, {'v', {'v', '<', '>'}},
        {'<', {'<', 'v', '^'}}, {'^', {'^', '<', '>'}}};
    auto in_range = [m, n](pair<int, int>& p) { return p.F >= 0 && p.F < m && p.S >= 0 && p.S < n; };

    while (!pque.empty()) {

        auto node = pque.top();
        auto [i, j, d] = node;
        pque.pop();
        seen.insert(tuple{i, j, d});

        if (maze[i][j] == 'E') continue;

        for (const auto nxtd : nxtdir[d]) {
            auto nxt = pair{i, j} + nxtloc[nxtd];
            auto nxtnode = tuple{nxt.F, nxt.S, nxtd};
            if (in_range(nxt) && maze[nxt.F][nxt.S] != '#' && !seen.contains(nxtnode)) {
                auto newcost = cost[node] + (nxtd == d ? 1 : 1001);
                if (!cost.contains(nxtnode) || cost[nxtnode] > newcost) {
                    cost[nxtnode] = newcost;
                    pque.push(nxtnode);
                    pred[nxtnode].push_back(node);
                } else if (cost[nxtnode] == newcost) {
                    pred[nxtnode].push_back(node);
                }
            }
        }
    }
    cout << cost[tuple{1, n - 2, '^'}] << endl;  // part 1

    set<pair<int, int>> found;

    function<int(node_t)> dfs = [&found, &pred, &dfs](node_t node) -> int {
        auto [i, j, d] = node;
        int children = found.contains(pair{i, j}) ? 0 : 1;
        found.insert(pair{i, j});
        for (auto nbr : pred[node])
            children += dfs(nbr);
        return children;
    };

    cout << dfs(tuple{1, n - 2, '^'}) << endl;  // part 2
}
