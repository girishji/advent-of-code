#include <bits/stdc++.h>
using namespace std;
using i64 = std::int64_t;
#define F first
#define S second

int main() {
    freopen("./13.txt", "r", stdin);
    vector<pair<int, int>> A, B, Prize;
    vector<pair<int, int>>* data[] = { &A, &B, &Prize };
    regex pat {R"(X.(\d+), Y.(\d+))"};
    int idx{};
    for (string line; getline(cin, line); ) {
        if (line.size() == 0) idx = 0;
        else {
            smatch matches;
            if (regex_search(line, matches, pat)) {
                data[idx++]->push_back(pair{stoi(matches[1].str()), stoi(matches[2].str())});
            }
        }
    }

    i64 tokens{};
    for (i64 delta : vector<i64>{0, 10000000000000}) {
        for (auto [a, b, pr] : views::zip(A, B, Prize)) {
            pair<i64, i64> p{pr.F + delta, pr.S + delta};
            auto D = a.F * b.S - b.F * a.S;
            if (D == 0) continue;
            i64 na = (p.F * b.S - p.S * b.F) / D;
            i64 nb = (p.S * a.F - p.F * a.S) / D;
            if (na >= 0 && nb >= 0 && (na * a.F + nb * b.F == p.F) && (na * a.S + nb * b.S == p.S)) {
                tokens += 3 * na + nb;
            }
        }
        cout << tokens << endl;
        tokens = 0;
    }
}
