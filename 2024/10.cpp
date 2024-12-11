#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second

int main() {
    // freopen("./tmp.txt", "r", stdin);
    freopen("./10.txt", "r", stdin);
    vector<string> topo;
    for (string line; getline(cin, line); ) {
        topo.push_back(line);
    }
    int m = (int)topo.size(), n = (int)topo[0].size();
    set<pair<int, int>> train_dest;

    auto in_range = [&](int i, int j) { return i >= 0 && i < m && j >= 0 && j < n; };

    function<int(int, int, int)> find_trail = [&](int x, int y, int level) -> int {
        if (!in_range(x, y) || level != topo[x][y] - '0') return 0;
        if (level == 9) {
            train_dest.insert(pair{x, y});
            return 1;
        }
        auto count = 0;
        for (int i = 0, j = 1, w = 0; w < 4; ++w) {
            count += find_trail(x + i, y + j, level + 1);
            tie(i, j) = tuple{j, -i};
        }
        return count;
    };

    int res1 = 0, res2 = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            train_dest.clear();
            res2 += find_trail(i, j, 0);
            res1 += (int)train_dest.size();
        }

    cout << res1 << " " << res2 << endl;
}
