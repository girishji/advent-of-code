#include <bits/stdc++.h>
using namespace std;
using namespace std::string_view_literals;
namespace rg = std::ranges;
namespace rv = std::ranges::views;
using i64 = std::int64_t;

vector<string> towels;

map<string, i64> possible;

i64 is_possible(string design) {
    if (design.empty()) return 1;
    if (!possible.contains(design)) {
        possible[design] = 0;
        for (const auto& t : towels) {
            if (design.starts_with(t)) {
                auto count = is_possible(design.substr(t.length()));
                possible[design] += count;
            }
        }
    }
    return possible[design];
}

int main() {
    freopen("./19.txt", "r", stdin);
    string line;
    getline(cin, line);
    for (const auto word : rv::split(line, ", "sv)) {
        string s(string_view{word});
        towels.push_back(s);
    }
    getline(cin, line);
    i64 res1{}, res2{};
    while (getline(cin, line)) {
        auto count = is_possible(line);
        if (count) res1++;
        res2 += count;
    }
    cout << res1 << " " << res2 << endl;
}
