#include <bits/stdc++.h>
using namespace std;
namespace rg = std::ranges;

// Function to find maximal cliques using Bron-Kerbosch algorithm
void bronKerbosch(set<string>& R, set<string>& P, set<string>& X,
                  map<string, set<string>>& graph,
                  vector<set<string>>& cliques) {
    if (P.empty() && X.empty()) {
        cliques.push_back(R); // Found a maximal clique
        return;
    }

    set<string> P_copy = P;
    for (string v : P_copy) {
        R.insert(v);
        set<string> neighbors = graph[v];
        set<string> newP, newX;

        rg::set_intersection(P, neighbors, inserter(newP, newP.end()));
        rg::set_intersection(X, neighbors, inserter(newX, newX.end()));

        bronKerbosch(R, newP, newX, graph, cliques);
        R.erase(v);
        P.erase(v);
        X.insert(v);
    }
}

int main() {
    vector<pair<string, string>> conns;
    freopen("./23.txt", "r", stdin);
    for (string line; getline(cin, line); ) {
        istringstream iss(line);
        string fr, to;
        getline(iss, fr, '-'), getline(iss, to, '-');
        conns.push_back(pair{fr, to});
    }

    map<string, set<string>> graph;
    for (const auto& [fr, to] : conns) {
        graph[fr].insert(to);
        graph[to].insert(fr);
    }

    set<string> party;
    for (const auto& [fr, to] : conns) {
        if (fr.starts_with("t") || to.starts_with("t")) {
            vector<string> third;
            rg::set_intersection(graph[fr], graph[to], back_inserter(third));
            for (const auto& cm : third) {
                vector<string> cmps = {fr, to, cm};
                rg::sort(cmps);
                party.insert(cmps[0] + cmps[1] + cmps[2]);
            }
        }
    }
    cout << party.size() << endl;

    // part 2
    set<string> R, P, X;
    for (const auto& [key, value] : graph) {
        P.insert(key);
    }
    vector<set<string>> cliques;
    bronKerbosch(R, P, X, graph, cliques);

    int maxc{-1};
    for (int i = 0; i < (int)cliques.size(); i++) {
        if (maxc == -1 || cliques[maxc].size() < cliques[i].size()) {
            maxc = i;
        }
    }
    for (string node : cliques[maxc]) {
        std::cout << node << ",";
    }
    std::cout << std::endl;
}
