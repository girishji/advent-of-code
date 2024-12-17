#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second

int main() {
    freopen("./14.txt", "r", stdin);
    int XMax{101}, YMax{103};
    vector<pair<int, int>> pos, vel;
    for (string line; getline(cin, line); ) {
        smatch matches;
        regex pat {R"((\d+),(\d+) v=(-?\d+),(-?\d+))"};
        if (regex_search(line, matches, pat)) {
            pos.push_back(pair{stoi(matches[1].str()), stoi(matches[2].str())});
            vel.push_back(pair{stoi(matches[3].str()), stoi(matches[4].str())});
        }
    }

    auto move = [&pos, &vel, XMax, YMax](int T) {
        vector<pair<int, int>> newpos;
        for (auto [p, v] : views::zip(pos, vel)) {
            auto [x, y] = p;
            auto [vx, vy] = v;
            auto xx = (x + vx * T) % XMax;
            xx = (xx < 0) ? XMax + xx : xx;
            auto yy = (y + vy * T) % YMax;
            yy = (yy < 0) ? YMax + yy : yy;
            newpos.push_back(pair{xx, yy});
        }
        return newpos;
    };

    auto safety = [XMax, YMax](vector<pair<int, int>> pos) -> int {
        int q1{}, q2{}, q3{}, q4{};
        for (auto [x, y] : pos) {
            if (x < XMax / 2 && y < YMax / 2) q1++;
            if (x < XMax / 2 && y > YMax / 2) q2++;
            if (x > XMax / 2 && y < YMax / 2) q3++;
            if (x > XMax / 2 && y > YMax / 2) q4++;
        }
        return q1 * q2 * q3 * q4;
    };

    auto print_tree = [XMax, YMax](vector<pair<int, int>> pos) {
        vector<string> grid;
        for (auto _ : views::iota(0, YMax)) grid.push_back(string(XMax, ' '));
        for (auto [x, y] : pos) grid[y][x] = 'X';
        for (auto& l : grid) cout << l << endl;
    };

    cout << safety(move(100)) << endl;

    vector<pair<int, int>> score;
    for (int i = 0; i < XMax * YMax; i++)
        score.push_back(pair{safety(move(i)), i});
    ranges::sort(score, ranges::less{}, &pair<int, int>::first);
    for (int i = 0; i < 10; i++) {
        print_tree(move(score[i].second));
        cout << "==============================================================" << endl << endl;
        cout << score[i].second << endl;
        cout << "==============================================================" << endl << endl;
    }
}


