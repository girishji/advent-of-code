#include <bits/stdc++.h>
using namespace std;
using namespace std::string_view_literals;
namespace rg = std::ranges;
namespace rv = std::ranges::views;
using i64 = std::int64_t;
#define F first
#define S second

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& p) {
    os << '(' << p.first << ", " << p.second << ')';
    return os;
}

int main() {
    // freopen("./test.txt", "r", stdin);
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
            if (isdigit(fr) || isdigit(to))
                pmemo[s] = idx_seq(npad[fr], npad[to], idx{0, 0});
            else
                pmemo[s] = idx_seq(dpad[fr], dpad[to], idx{0, 1});
        }
        return pmemo[s];
    };

    map<string, string> memo;

    auto path_seq = [&memo, &pair_seq](string pathstr) -> string {
        if (!memo.contains(pathstr)) {
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
            auto turns = [](const string& x) {
                int tcount{};
                char prev = x[0];
                for (int i = 1; i < (int)x.length(); i++) {
                    if (prev != x[i]) {
                        tcount++;
                        prev = x[i];
                    }
                }
                return tcount;
            };
            rg::sort(paths, [&turns](const string& a, const string& b) {
                    return turns(a) < turns(b); });
            memo[pathstr] = rg::min(paths, [](const string& a, const string& b) {
                    return a.length() < b.length(); });
        }
        return memo[pathstr];
    };

    function<i64(string, int)> minseqlen = [&minseqlen, &path_seq](string seq, int lvl) ->i64 {
        // cout << seq << " lvl: " << lvl << endl;
        if (lvl == 0) return seq.length();
        i64 minlen{};
        seq.pop_back();
        for (const auto word : std::views::split(seq, "A"sv)) {
            string partial(string_view{word});
            partial += "A";
            auto path = path_seq(partial);
            minlen += minseqlen(path, lvl - 1);
        }
        return minlen;
    };

    i64 complexity{};
    for (const auto& code : codes) {
        complexity += minseqlen(code, 2 + 1) * stoi(code.substr(0, 3));
    }
    cout << complexity << endl;
    complexity = 0;
    for (const auto& code : codes) {
        complexity += minseqlen(code, 25 + 1) * stoi(code.substr(0, 3));
    }
    cout << complexity << endl;
}
