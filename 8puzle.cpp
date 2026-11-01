
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;

struct Node {
    vector<int> state;
    int g, h;
    string path;

    int f() const {
        return g + h;} };

struct Compare {
    bool operator()(const Node& a, const Node& b) const {
        return a.f() > b.f();
    }
};

int heuristic(const vector<int>& state) {
    int h = 0;

    for (int i = 0; i < 9; i++) {
        if (state[i] == 0)
            continue;

        int value = state[i] - 1;

        int currentRow = i / 3;
        int currentCol = i % 3;

        int goalRow = value / 3;
        int goalCol = value % 3;

        h += abs(currentRow - goalRow)
           + abs(currentCol - goalCol);
    }

    return h;
}

int main() {
    vector<int> start(9);

    cout << "Enter the initial state (0 for blank):\n";

    for (int i = 0; i < 9; i++) {
        cin >> start[i];
    }

    priority_queue<Node, vector<Node>, Compare> pq;
    set<vector<int>> visited;

    pq.push({start, 0, heuristic(start), ""});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    char moves[] = {'U', 'D', 'L', 'R'};

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (visited.count(cur.state))
            continue;

        visited.insert(cur.state);

        if (cur.h == 0) {
            cout << "\nSolution found!\n";
            cout << "Moves: " << cur.path << "\n";
            cout << "Minimum moves: " << cur.g << "\n";
            return 0;
        }

        int zero = find(cur.state.begin(),
                        cur.state.end(), 0)
                   - cur.state.begin();

        int r = zero / 3;
        int c = zero % 3;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr < 0 || nr >= 3 ||
                nc < 0 || nc >= 3)
                continue;

            vector<int> next = cur.state;

            swap(next[zero], next[nr * 3 + nc]);

            if (visited.count(next))
                continue;

            pq.push({
                next,
                cur.g + 1,
                heuristic(next),
                cur.path + moves[i]
            });
        }
    }

    cout << "No solution found.\n";

    return 0;
}
