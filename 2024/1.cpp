// Part 2

#include <bits/stdc++.h>
using namespace std;
namespace rn = ranges;

int main() {
    freopen("./1.txt", "r", stdin);
    vector<int> n1, n2;
    int i1, i2;
    while(cin >> i1 >> i2) {
        n1.push_back(i1);
        n2.push_back(i2);
    }
    rn::sort(n1);
    rn::sort(n2);
    int res = 0;
    unsigned long j = 0;
    int cnt1 = 0;
    for(unsigned long i = 0; i < n1.size(); i++) {
        cnt1++;
        if (i + 1 < n1.size() && n1[i] == n1[i + 1]) {
            continue;
        }
        int cnt2 = 0;
        for(; j < n2.size(); j++) {
            if (n2[j] < n1[i]) continue;
            if (n2[j] > n1[i]) break;
            cnt2++;
        }
        res += n1[i] * cnt1 * cnt2;
        cnt1 = 0;
    }
    cout << res;
}

