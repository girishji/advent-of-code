#include <bits/stdc++.h>
using namespace std;
using i64 = std::int64_t;

i64 next_secret(i64 seed) {
    auto mix = [](i64 m, i64 n) { return m ^ n; };
    auto prune = [](i64 m) { return m % 16777216; };
    i64 res{seed};
    res = prune(mix(res * 64, res));
    res = prune(mix(res / 32, res));
    res = prune(mix(res * 2048, res));
    return res;
}

int main() {
    freopen("./22.txt", "r", stdin);
    vector<int> nums;
    for (int num; cin >> num; )
        nums.push_back(num);

    i64 res{};
    for (i64 num : nums) {
        for (int i = 0; i < 2000; i++)
            num = next_secret(num);
        res += num;
    }
    cout << res << endl;

    map<tuple<int, int, int, int>, i64> bananas;
    map<tuple<int, int, int, int>, set<i64>> seen;
    for (i64 num : nums) {
        int a{}, b{}, c{}, d{};
        i64 prev{num % 10}, secr{num};
        for (int i = 0; i < 2000; i++) {
            secr = next_secret(secr);
            auto cur = secr % 10;
            tie(a, b, c, d) = tuple{b, c, d, (int)(cur - prev)};
            prev = cur;
            if (i > 2) {
                auto key = tuple{a, b, c, d};
                if (!seen[key].contains(num)) {
                    seen[key].insert(num);
                    bananas[key] += cur;
                }
            }
        }
    }
    auto price = *ranges::max_element(bananas, [](const auto& a, const auto& b) {
            return a.second < b.second;});
    cout << price.second << endl;
}
