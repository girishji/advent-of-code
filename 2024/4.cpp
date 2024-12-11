#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("./4.txt", "r", stdin);
    vector<string> m;
    for (string line; getline(cin, line);) {
        m.push_back(line);
    }
    int res = 0;
    int msz = (int)m.size(), nsz = (int)m[0].size();
    auto X{"XMAS"};
    auto valid = [&msz, &nsz](int i, int j) {return (i >= 0 && i < msz && j >= 0 && j < nsz);};
    for (int i = 0; i < msz; i++) {
        for (int j = 0; j < nsz; j++) {
            for (const auto& n : std::vector{
                    pair{0, 1}, pair{0, -1},
                    pair{1, 0}, pair{-1, 0},
                    pair{1, 1}, pair{-1, -1},
                    pair{1, -1}, pair{-1, 1},
                    }) {
                auto match = true;
                for (int k = 0; k < 4; k++) {
                    int ii = i + k*n.first, jj = j + k*n.second;
                    if (!valid(ii, jj) || m[ii][jj] != X[k]) {
                        match = false;
                        break;
                    }
                }
                if (match) res++;
            }
        }
    }
    cout << res << endl;
    res = 0;
    for (int i = 1; i < msz-1; i++) {
        for (int j = 1; j < nsz-1; j++) {
            if (m[i][j] != 'A') continue;
            if (((m[i-1][j-1] == 'M' && m[i+1][j+1] == 'S') ||
                    (m[i-1][j-1] == 'S' && m[i+1][j+1] == 'M')) &&
                    ((m[i-1][j+1] == 'M' && m[i+1][j-1] == 'S') ||
                     (m[i-1][j+1] == 'S' && m[i+1][j-1] == 'M'))) {
                res++;
            }
        }
    }
    cout << res << endl;
}
