#include <bits/stdc++.h>
using namespace std;
using namespace std::string_view_literals;
namespace rg = std::ranges;
namespace rv = std::ranges::views;
using u64 = std::uint64_t;
#define F first
#define S second

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

    // part 1
    auto output = [&prog](int A, int B, int C, bool verify) {
        vector<int> res;
        for (int i = 0; i < (int)prog.size(); i += 2) {
            int opcode = prog[i], operand = prog[i + 1];
            vector<int> combo{0, 1, 2, 3, A, B, C};
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
                if (verify && res.back() != prog[res.size() - 1])
                    return vector<int>{};
            } else if (opcode == 6)
                B = A >> combo[operand];
            else if (opcode == 7)
                C = A >> combo[operand];
        }
        // if (res.size() != prog.size()) {
        //     for (const auto& el : res) { cout << el << " "; }; cout << endl;
        //     for (const auto& el : prog) { cout << el << " "; }; cout << endl;
        // }
        // return verify ? (res.size() != prog.size() ? vector<int>{} : res) : res;
        return res;
    };

    // part 1
    for (const auto& n : output(rA, rB, rC, false)) { cout << n << ","; }; cout << endl;

    // part 2
    // B = A % 8;
    // B = B ^ 2;
    // C = A >> B;
    // A = A >> 3;  -> A should be at least 1<<(3*prog.size())
    // B = B ^ C;
    // B = B ^ 7;
    // B % 8 == 2;

    int A = 1 << (3 + prog.size());
    while (true) {
        auto outp = output(A, 0, 0, true);
        // if (!outp.empty()) {
        if (!outp.empty() && prog.size() != outp.size()) {
            for (const auto& el : outp) { cout << el << ","; }; cout << endl;
            for (const auto& el : prog) { cout << el << ","; }; cout << endl;
            cout << A << endl;
            // break;
        }
        A++;
    }
}
