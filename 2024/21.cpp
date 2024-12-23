#include <bits/stdc++.h>
using namespace std;
namespace rv = std::ranges::views;
using i64 = std::int64_t;
#define F first
#define S second

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& p) {
    os << '(' << p.first << ", " << p.second << ')';
    return os;
}

int main() {
    freopen("./21.txt", "r", stdin);
    vector<string> codes;
    for (string line; cin >> line; )
        codes.push_back(line);

    using idx = pair<int, int>;

    map<char, idx> npad {{'0', idx{1, 0}}, {'A', idx{2, 0}},
        {'1', idx{0, 1}}, {'2', idx{1, 1}}, {'3', idx{2, 1}},
        {'4', idx{0, 2}}, {'5', idx{1, 2}}, {'6', idx{2, 2}},
        {'7', idx{0, 3}}, {'8', idx{1, 3}}, {'9', idx{2, 3}}};

    map<char, idx> dpad {{'<', idx{0, 0}}, {'v', idx{1, 0}}, {'>', idx{2, 0}},
        {'^', idx{1, 1}}, {'A', idx{2, 1}}};

    function<vector<string>(idx, idx, idx)> idx_seq =
        [&idx_seq](idx fr, idx to, idx vac) -> vector<string> {
        if (fr == to) return {"A"};
        if (fr == vac) return {};
        vector<string> vs;
        auto insert = [&vs](char ch, vector<string> ps) {
            for (const auto& p : ps)
                vs.push_back(ch + p);
        };
        if (to.F < fr.F) insert('<', idx_seq(idx{fr.F - 1, fr.S}, to, vac));
        if (to.S > fr.S) insert('^', idx_seq(idx{fr.F, fr.S + 1}, to, vac));
        if (to.S < fr.S) insert('v', idx_seq(idx{fr.F, fr.S - 1}, to, vac));
        if (to.F > fr.F) insert('>', idx_seq(idx{fr.F + 1, fr.S}, to, vac));
        return vs;
    };

    map<string, vector<string>> pmemo;

    auto pair_seq = [&pmemo, &idx_seq, &npad, &dpad](char fr, char to) {
        string s{fr, to};
        if (!pmemo.contains(s)) {
            vector<string> paths;
            if (isdigit(fr) || isdigit(to))
                paths = idx_seq(npad[fr], npad[to], idx{0, 0});
            else
                paths = idx_seq(dpad[fr], dpad[to], idx{0, 1});
            // remove zigzag's - reddit hint
            for (auto it = paths.begin(); it != paths.end(); ) {
                bool removed{false};
                for (auto [a, b, c] : *it | rv::adjacent<3>) {
                    if (a == c && a != b && b != c) {
                        it = paths.erase(it);
                        removed = true;
                        break;
                    }
                }
                if (!removed) it++;
            }
            pmemo[s] = paths;
        }
        return pmemo[s];
    };

    map<string, vector<string>> smemo;

    auto path_seq = [&smemo, &pair_seq](string pathstr) -> vector<string> {
        if (!smemo.contains(pathstr)) {
            string s = 'A' + pathstr;
            vector<string> paths{""};
            for (unsigned long i = 0; i < s.length() - 1; i++) {
                auto seqs = pair_seq(s[i], s[i + 1]);
                vector<string> npaths;
                for (auto [path, seq] : rv::cartesian_product(paths, seqs)) {
                    npaths.push_back(path + seq);
                }
                paths.swap(npaths);
            }
            smemo[pathstr] = paths;
        }
        return smemo[pathstr];
    };

    map<pair<string, int>, i64> memo;

    function<i64(string, int)> dfs = [&dfs, &memo, &path_seq](string sequence, int lvl) ->i64 {
        if (lvl == 0) return sequence.length();
        if (sequence == "A") return 1;
        i64 minlen{numeric_limits<i64>::max()};
        for (auto seq : path_seq(sequence)) {
            i64 mlen{};
            seq.pop_back();
            for (const auto word : rv::split(seq, "A"sv)) {
                string partial(string_view{word});
                partial += "A";
                pair key{partial, lvl};
                if (!memo.contains(key)) {
                    memo[key] = dfs(partial, lvl - 1);
                }
                mlen += memo[key];
            }
            minlen = min(minlen, mlen);
        }
        return minlen;
    };

    i64 complexity{};
    for (const auto& code : codes) {
        complexity += dfs(code, 2 + 1) * stoi(code.substr(0, 3));
    }
    cout << complexity << endl;
    complexity = 0;
    for (const auto& code : codes) {
        complexity += dfs(code, 25 + 1) * stoi(code.substr(0, 3));
    }
    cout << complexity << endl;
}
