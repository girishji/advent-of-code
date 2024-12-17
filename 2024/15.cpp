#include <bits/stdc++.h>
using namespace std;
namespace rg = std::ranges;
namespace rv = std::ranges::views;
using u64 = std::uint64_t;
using i64 = std::int64_t;
#define F first
#define S second

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& p) {
    os << '(' << p.first << ", " << p.second << ')';
    return os;
}

int main() {
    freopen("./15.txt", "r", stdin);
    vector<string> wh;
    string mvmt;
    for (string line; getline(cin, line); ) {
        if (line.size() == 0) continue;
        if (line[0] == '#') wh.push_back(line);
        else mvmt += line;
    }
    vector<string> saved(wh.begin(), wh.end());

    map<char, pair<int, int>> posmap = {{'<', pair{0, -1}},
        {'^', pair{-1, 0}}, {'>', pair{0, 1}}, {'v', pair{1, 0}}};

    auto step = [&posmap](char m, pair<int, int> p) {
        return pair{posmap[m].F + p.F, posmap[m].S + p.S};
    };

    auto step_back = [&posmap](char m, pair<int, int> p) {
        return pair{posmap[m].F * -1 + p.F, posmap[m].S * -1 + p.S};
    };

    auto indices = rv::cartesian_product(rv::iota(0, (int)wh.size()), rv::iota(0, (int)wh[0].size()));
    pair<int, int> cur = *ranges::find_if(indices, [&wh](const auto& idx) {
            auto [i, j] = idx; return wh[i][j] == '@'; });

    for (auto mt : mvmt) {
        auto nxt = step(mt, cur);
        if (wh[nxt.F][nxt.S] == '#') continue;
        if (wh[nxt.F][nxt.S] == '.') {
            swap(wh[cur.F][cur.S], wh[nxt.F][nxt.S]);
            cur = nxt;
        } else if (wh[nxt.F][nxt.S] == 'O') {
            pair<int, int> vacant{step(mt ,nxt)};
            for (; wh[vacant.F][vacant.S] == 'O'; vacant = step(mt, vacant)) ;
            if (wh[vacant.F][vacant.S] == '.') {
                wh[vacant.F][vacant.S] = 'O';
                wh[nxt.F][nxt.S] = '@';
                wh[cur.F][cur.S] = '.';
                cur = nxt;
            }
        }
    }
    indices = rv::cartesian_product(rv::iota(0, (int)wh.size()), rv::iota(0, (int)wh[0].size()));
    auto gps = ranges::fold_left(indices, 0, [&wh](int acc, const pair<int, int>& p) {
            return acc + (wh[p.F][p.S] == 'O' ? 100 * p.F + p.S : 0);
            });
    cout << gps << endl;

    // part 2
    wh.clear();
    for (auto& l : saved) {
        string s{};
        for (const auto ch : l) {
            if (ch == '@') s += "@.";
            else if (ch == 'O') s += "[]";
            else s += ch, s+= ch;
        }
        wh.push_back(s);
    }

    indices = rv::cartesian_product(rv::iota(0, (int)wh.size()), rv::iota(0, (int)wh[0].size()));
    cur = *ranges::find_if(indices, [&wh](const auto& idx) {
            auto [i, j] = idx; return wh[i][j] == '@'; });

    using nodes = set<pair<int, int>>;
    using node = pair<int, int>;
    function<optional<nodes>(char, node&)> dfs = [&wh, &step, &dfs](char mt, node& rt) -> optional<nodes> {
        auto val = wh[rt.F][rt.S];
        if (val == '.') return nodes();
        if (val == '#') return nullopt;
        nodes cnctd{{rt}};
        auto nxt = step(mt, rt);
        auto stree = dfs(mt, nxt);
        if (!stree) return nullopt;
        cnctd.insert(stree.value().begin(), stree.value().end());
        if (wh[nxt.F][nxt.S] == '[')
            nxt = pair{nxt.F, nxt.S + 1};
        else if (wh[nxt.F][nxt.S] == ']')
            nxt = pair{nxt.F, nxt.S - 1};
        stree = dfs(mt, nxt);
        if (!stree) return nullopt;
        cnctd.insert(stree.value().begin(), stree.value().end());
        return cnctd;
    };

    for (const auto& mt : mvmt) {

        auto nxt = step(mt, cur);
        if (wh[nxt.F][nxt.S] == '#') continue;
        if (wh[nxt.F][nxt.S] == '.') {
            swap(wh[cur.F][cur.S], wh[nxt.F][nxt.S]);
            cur = nxt;
            continue;
        }

        if (mt == '<' || mt == '>') {
            auto it = step(mt, cur);
            while (wh[it.F][it.S] == ']' || wh[it.F][it.S] == '[') it = step(mt, it);
            if (wh[it.F][it.S] == '.') {
                do {
                    auto prev = step_back(mt, it);
                    swap(wh[prev.F][prev.S], wh[it.F][it.S]);
                    if (wh[it.F][it.S] == '@') break;
                    it = prev;
                } while (true);
                cur = step(mt, cur);
            }
        } else {
            auto cnctd = dfs(mt, cur);
            if (!cnctd) continue;
            auto boxes = vector<pair<int, int>>(cnctd.value().begin(), cnctd.value().end());

            if (mt == '^')
                rg::sort(boxes, {}, &pair<int, int>::first);
            else
                rg::sort(boxes, greater<int>{}, &pair<int, int>::first);
            for (auto p : boxes) {
                auto nxt = step(mt, p);
                swap(wh[nxt.F][nxt.S], wh[p.F][p.S]);
            }
            if (!boxes.empty()) cur = step(mt, cur);
        }
    }
    indices = rv::cartesian_product(rv::iota(0, (int)wh.size()), rv::iota(0, (int)wh[0].size()));
    gps = ranges::fold_left(indices, 0, [&wh](int acc, const pair<int, int>& p) {
            return acc + (wh[p.F][p.S] == '[' ? 100 * p.F + p.S : 0);
            });
    cout << gps << endl;
}
