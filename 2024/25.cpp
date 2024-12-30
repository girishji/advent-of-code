#include <bits/stdc++.h>
using namespace std;
using namespace string_view_literals;
namespace rg = ranges;
namespace rv = ranges::views;
using i64 = int64_t;
#define F first
#define S second

int main() {
    freopen("./25.txt", "r", stdin);
    vector<vector<int>> keys, locks;
    for (string line; getline(cin, line); ) {
        auto iskey = (line == ".....");
        vector<int> ht(5, 0);
        for (int i = 0; i < 5; i++) {
            getline(cin, line);
            for (int j = 0; j < 5; j++) {
                if (line[j] == '#')
                    ht[j]++;
            }
        }
        if (iskey)
            keys.push_back(ht);
        else
            locks.push_back(ht);
        getline(cin, line);
        getline(cin, line);
    }
    int res{};
    for (const auto [l, k] : rv::cartesian_product(locks, keys)) {
        auto comb = rv::zip(l, k);
        if (all_of(comb.cbegin(), comb.cend(),
                    [](pair<int, int> p) { return p.F + p.S < 6; })) {
            res++;
        }
    }
    cout << res << endl;
}
