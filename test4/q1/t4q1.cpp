#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

enum loc {
    ROAD = 0 ,
    TREE     ,
    GARAGE   ,
    WAREHOUSE,
    AIRPORT  ,
};

const array<pii, 4> dir = {{
    { 0,  1},
    { 0, -1},
    { 1,  0},
    {-1,  0},
}};

vector<vector<int>> get_dist(vector<vector<int>>& g, queue<pii>& q) {
    int m = g.size(), n = g[0].size();
    vector<vector<int>> dist(m, vector<int>(n, INT32_MAX));
    while (!q.empty()) {
        auto[i, j] = q.front();
        q.pop();
        for (auto[di, dj]: dir) {
            int x = i + di, y = j + dj;
            if (
                (x >= 0 && x < m && y >= 0 && y < n) &&
                g[x][y] != TREE && dist[i][j] + 1 < dist[x][y]
            ) {
                q.push({x, y});
            }
        }
    }

    return dist;
}

int main() {            // Time complexity O(h * w)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // freopen("inp.txt", "r", stdin);
    // ^^^ uncomment when you put in an inp.txt file with test cases

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int h, w, c;
        cin >> h >> w >> c;
        
        queue<pii> qG, qA;
        vector<vector<int>> g(h, vector<int>(w));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> g[i][j];
                if (g[i][j] == AIRPORT) {
                    qA.push({i, j});
                }
                if (g[i][j] == GARAGE) {
                    qG.push({i, j});
                }
            }
        }

        vector<vector<int>> dA, dG;
        dA = get_dist(g, qA);
        dG = get_dist(g, qG);
        int ans = 0;

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (g[i][j] == WAREHOUSE) {
                    ans = max(
                        (c - dG[i][j]) / dA[i][j] - 1,
                        ans
                    );
                }
            }
        }

        cout << "#" << t << " " << ans << endl; 
    }

}