#include <bits/stdc++.h>
using namespace std;

using u64 = std::uint64_t;
using stones_t = unordered_map<u64, u64>;

template <int N>
auto blink = [](stones_t stones) {
    stones_t next;
    for (auto _ : views::iota(0, N)) {
        for (const auto& [s, count] : stones) {
            if (s == 0) {
                next[1] += count;
            } else {
                auto ss = to_string(s);
                if (ss.length() % 2 == 0) {
                    auto sz = ss.size() / 2;
                    next[stoull(ss.substr(0, sz))] += count;
                    next[stoull(ss.substr(sz, sz))] += count;
                } else {
                    next[s * 2024] += count;
                }
            }
        }
        swap(stones, next);
        next.clear();
    }
    return ranges::fold_left(stones | views::values, 0, plus<u64>());
};

int main() {
    stones_t stones;
    freopen("./11.txt", "r", stdin);
    for (string s; cin >> s; ) {
        stones[stoull(s)] = 1;
    }

    auto const part1 = blink<25>;
    cout << part1(stones) << endl;
    auto const part2 = blink<75>;
    cout << part2(stones) << endl;
}
