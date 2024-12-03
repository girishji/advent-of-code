#include <bits/stdc++.h>
using namespace std;
namespace rng = ranges;

int main() {
    freopen("./day3.input.txt", "r", stdin);
    int res = 0;
    regex pat {R"(mul\((\d{1,3}),(\d{1,3})\))"};
    for(string line; getline(cin, line); ) {
        for(sregex_iterator p(line.begin(), line.end(), pat); p != sregex_iterator(); ++p) {
            smatch m = *p;
            res += stoi(m[1]) * stoi(m[2]);
        }
    }
    cout << res << endl;
    //
    // Clear EOF state
    cin.clear();
    freopen("./day3.input.txt", "r", stdin);
    res = 0;
    bool enabled = true;
    pat = R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))";
    for(string line; getline(cin, line); ) {
        for(sregex_iterator p(line.begin(), line.end(), pat); p != sregex_iterator(); ++p) {
            smatch m = *p;
            if(enabled && m[0].str().substr(0, 3) == "mul") {
                res += stoi(m[1]) * stoi(m[2]);
            } else if(m[0].str() == "do()") {
                enabled = true;
            } else {
                enabled = false;
            }
        }
    }
    cout << res << endl;
}
