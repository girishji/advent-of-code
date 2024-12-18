#include <bits/stdc++.h>
using namespace std;
using i64 = std::int64_t;

int main() {
    // freopen("./test.txt", "r", stdin);
    freopen("./17.txt", "r", stdin);
    vector<int> prog;
    for (string word; cin >> word; ) {
        for (const auto w : views::split(word, ","sv)) {
            if (isdigit(string_view(w).front()))
                prog.push_back(stoi(string_view(w).data()));
        }
    }
    int rA = prog[0], rB = prog[1], rC = prog[2];
    prog.erase(prog.begin(), prog.begin() + 3);

    auto output = [&prog](i64 A, i64 B, i64 C) {
        vector<i64> res;
        for (int i = 0; i < (int)prog.size(); i += 2) {
            int opcode = prog[i], operand = prog[i + 1];
            vector<i64> combo{0, 1, 2, 3, A, B, C};
            if (opcode == 0)
                A >>= combo[operand];
            else if (opcode == 1)
                B ^= operand;
            else if (opcode == 2)
                B = combo[operand] % 8;
            else if (opcode == 3) {
                if (A != 0) i = operand - 2;
            } else if (opcode == 4)
                B ^= C;
            else if (opcode == 5) {
                res.push_back(combo[operand] % 8);
            } else if (opcode == 6)
                B = A >> combo[operand];
            else if (opcode == 7)
                C = A >> combo[operand];
        }
        return res;
    };

    // part 1
    ostringstream oss;
    for (const auto& n : output(rA, rB, rC)) { oss << n << ","; };
    string s = oss.str(); s.pop_back();
    cout << s << endl;

    // part 2
    vector<i64> res;
    function<void(i64, int)> findnum = [&prog, &res, &output, &findnum](i64 A, int idx) {
        if (idx < 0) {
            res.push_back(A >> 3);
            return;
        }
        for (int i = 0; i < 8; i++) {
            auto o = output(A + i, 0, 0);
            if (!o.empty() && o.front() == prog[idx]) {
                findnum((A + i) * 8, idx - 1);
            }
        }
    };

    findnum(0, (int)prog.size() - 1);
    ranges::sort(res);
    cout << res[0] << endl;
}
