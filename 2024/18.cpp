#include <bits/stdc++.h>
using namespace std;
namespace rg = std::ranges;
namespace rv = std::ranges::views;
#define F first
#define S second

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& p) {
    os << '(' << p.first << ", " << p.second << ')';
    return os;
}

pair<int, int> operator+(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

int main() {
    vector<pair<int, int>> fall;
    freopen("./18.txt", "r", stdin);
    int i, j;
    for (char ch; cin >> i >> ch >> j; )
        fall.push_back(pair{i, j});

    set<pair<int, int>> bytes(fall.begin(), fall.begin() + 1024);
    int m{71}, n{71};

    for (int byteidx = 1024; byteidx < (int)fall.size(); byteidx++) {

        // Dijkstra
        using node_t = tuple<int, int, char>;
        map<node_t, int> cost;
        cost[tuple{0, 0, '>'}] = 0;
        cost[tuple{0, 0, 'v'}] = 0;
        auto cmp = [&cost](node_t l, node_t m) { return cost[l] > cost[m];};
        priority_queue<node_t, vector<node_t>, decltype(cmp)> pque(cmp);
        pque.push(tuple{0, 0, '>'});
        pque.push(tuple{0, 0, 'v'});
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

            if (i == m - 1 && j == n - 1) continue;

            for (const auto nxtd : nxtdir[d]) {
                auto nxt = pair{i, j} + nxtloc[nxtd];
                auto nxtnode = tuple{nxt.F, nxt.S, nxtd};
                if (in_range(nxt) && !bytes.contains(nxt) && !seen.contains(nxtnode)) {
                    auto newcost = cost[node] + 1;
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
        if (byteidx == 1024) {
            cout << min(cost[tuple{m - 1, n - 1, 'v'}], cost[tuple{m - 1, n - 1, '>'}]) << endl;
        }
        if (!cost.contains(tuple{m - 1, n - 1, 'v'}) && !cost.contains(tuple{m - 1, n - 1, '>'})) {
            cout << fall[byteidx - 1] << endl;
            break;
        }
        bytes.insert(fall[byteidx]);
    }
}
