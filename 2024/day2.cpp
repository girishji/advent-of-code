#include <bits/stdc++.h>
using namespace std;
namespace rng = ranges;

auto ge = [](vector<int>& v) {
    return ranges::adjacent_find(v, std::greater_equal<int>());
};
auto le = [](vector<int>& v) {
    return ranges::adjacent_find(v, std::less_equal<int>());
};
auto df = [](vector<int>& v) {
    return ranges::adjacent_find(v,
                                 [](int a, int b) { return abs(a - b) > 3; });
};
vector<function<vector<int>::iterator(vector<int>&)>> lambdas {df, ge, le};

bool safe(vector<int>& vec) {
    return (ge(vec) == vec.end() || le(vec) == vec.end()) &&
           df(vec) == vec.end();
}

int main() {
    freopen("./day2.input.txt", "r", stdin);
    string line;
    int res1 = 0, res2 = 0;
    while(getline(cin, line)) {
        stringstream ss(line);
        int n;
        vector<int> vec;
        while(ss >> n) vec.push_back(n);
        if(safe(vec)) {
            res1++;
            res2++;
        } else {
            for(auto& lbd : lambdas) {
                auto v(vec);
                auto it = lbd(v);
                if(it != v.end()) {
                    auto dist = distance(v.begin(), it);
                    v.erase(it + 1);
                    if(safe(v)) {
                        res2++;
                        break;
                    }
                    v = vec;
                    v.erase(v.begin() + dist);
                    if(safe(v)) {
                        res2++;
                        break;
                    }
                }
            }
        }
    }
    cout << res1 << " " << res2;
}
