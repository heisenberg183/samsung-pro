#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int update_ans(int idx, int from, int to, int invariant, 
               const unordered_map<int, set<int>>& inv2var) {
    if (inv2var.find(invariant) == inv2var.end()) { return 0; }
    if (to < from) { swap(from, to); }

    const set<int>& v = inv2var.at(invariant);

    return distance(
        idx == 1 ? 
            lower_bound(v.begin(), v.end(), from) :
            upper_bound(v.begin(), v.end(), from) ,
        upper_bound(v.begin(), v.end(), to)
    );
}

int main() {                // Time complexity O(n log n)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("inp.txt", "r", stdin);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n, m; 
        cin >> n >> m;

        vector<pii> ptc(n);
        // all points wrt x value and y value, sorted by the other coordinate value
        unordered_map<int, set<int>> x2y, y2x;
        for (int i = 0; i < n; i++) {
            cin >> ptc[i].first;
        }
        for (int i = 0; i < n; i++) {
            cin >> ptc[i].second;
        }
        for (auto[x, y]: ptc) {
            x2y[x].insert(y);
            y2x[y].insert(x);
        }

        ptc = vector<pii>(m);
        for (int i = 0; i < m; i++) {
            cin >> ptc[i].first;
        }
        for (int i = 0; i < m; i++) {
            cin >> ptc[i].second;
        }

        auto[px, py] = ptc[0];
        int ans = 0;

        for (int i = 1; i < m; i++) {
            auto[x, y] = ptc[i];
            bool x_axis = (x == px);
            
            if (x_axis) {
                ans += update_ans(i, py, y, x, x2y);
            } else {
                ans += update_ans(i, px, x, y, y2x);
            }
            px = x; py = y;
        }

        cout << "#" << t << " " << ans << endl;
    }

}