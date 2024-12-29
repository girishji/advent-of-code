#include <bits/stdc++.h>
using namespace std;
namespace rg = std::ranges;
namespace rv = std::ranges::views;

int main() {
    freopen("./24.txt", "r", stdin);
    map<string, int> input;
    using conn_t = tuple<string, string, string, string>;
    vector<conn_t> conns;
    for (string line; getline(cin, line); ) {
        istringstream iss(line);
        int bit;
        if (string wire; iss >> wire >> bit) {
            wire.pop_back();
            input[wire] = bit;
        }
        iss.clear();
        iss.seekg(0);
        if (string w1, op, w2, arr, w3; iss >> w1 >> op >> w2 >> arr >> w3) {
            conns.push_back(tuple{w1, op, w2, w3});
        }
    }

    auto oper = [](string opcode, int a, int b) {
        if (opcode == "AND")
            return a & b;
        else if (opcode == "XOR")
            return a ^ b;
        else
            return a | b;
    };

    auto binadd = [&oper, &conns, &input]() -> map<string, int> {
        vector<conn_t> cns(conns);
        map<string, int> inp(input);
        bool reduced = true;
        while (!cns.empty() && reduced) {
            reduced = false;
            for (auto it = cns.begin(); it != cns.end(); ) {
                auto [a, op, b, c] = *it;
                if (inp.contains(a) && inp.contains(b)) {
                    inp[c] = oper(op, inp[a], inp[b]);
                    it = cns.erase(it);
                    reduced = true;
                } else {
                    it++;
                }
            }
        }
        return inp;
    };

    auto value_of = [](string name, map<string, int>& inp) {
        string res;
        for (const auto& [k, v] : inp) {
            if (k.starts_with(name)) {
                res = to_string(v) + res;
            }
        }
        return stoul(res, nullptr, 2);
    };

    // part 1

    auto inp = binadd();

    uint64_t Z = value_of("z", inp);
    cout << Z << endl;

    // part 2

    uint64_t X = value_of("x", input), Y = value_of("y", input);

    vector<int> defectz, defectn;
    for (int i = 0; i < (int)conns.size(); i++) {
        const auto [a, op, b, c] = conns[i];
        if (c.starts_with("z") && op != "XOR" && c != "z45")
            defectz.push_back(i);
        if (!c.starts_with("z") && op == "XOR" &&
                !a.starts_with("x") && !a.starts_with("y") &&
                !b.starts_with("x") && !b.starts_with("y"))
            defectn.push_back(i);
    }

    vector<pair<int, int>> defectxy;
    for (int i = 0; i < (int)45; i++) {
        string idx = (i < 10 ? "0" : "") + to_string(i);
        string xidx = "x" + idx, yidx = "y" + idx;
        int fidx{-1}, sidx{-1};
        for (int j = 0; j < (int)conns.size(); j++) {
            auto [lh, op, rh, rs] = conns[j];
            if ((lh == xidx && rh == yidx) || (lh == yidx && rh == xidx)) {
                if (fidx == -1)
                    fidx = j;
                else
                    sidx = j;
            }
        }
        if (fidx >= 0 && sidx >= 0) {
            defectxy.push_back(pair{fidx, sidx});
        }
    }

    vector<int> idx(defectn.size());
    rg::iota(idx, 0);
    do {
        for (int i = 0; i < (int)defectz.size(); i++) {
            auto [a, b] = tuple{defectz[i], defectn[idx[i]]};
            swap(get<3>(conns[a]), get<3>(conns[b]));
        }

        for (auto [x, y] : defectxy) {
            swap(get<3>(conns[x]), get<3>(conns[y]));
            inp = binadd();
            uint64_t Z2 = value_of("z", inp);
            if (Z2  == X + Y) {
                vector<string> res{get<3>(conns[x]), get<3>(conns[y])};
                for (const auto& el : defectn) {
                    res.push_back(get<3>(conns[el]));
                }
                for (const auto& el : defectz) {
                    res.push_back(get<3>(conns[el]));
                }
                rg::sort(res);
                for (const auto& el : res) { cout << el << ","; }; cout << endl;
                break;
            }
            swap(get<3>(conns[x]), get<3>(conns[y]));
        }

        for (int i = 0; i < (int)defectz.size(); i++) {
            auto [a, b] = tuple{defectz[i], defectn[idx[i]]};
            swap(get<3>(conns[a]), get<3>(conns[b]));
        }
    } while (rg::next_permutation(idx).found);
}
