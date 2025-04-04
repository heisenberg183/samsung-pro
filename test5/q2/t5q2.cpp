#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int main(int argc, char* argv[]) {      // Time complexity O(n log n)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("inp.txt", "r", stdin);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n), b(m);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < m; i++) {
            cin >> b[i];
        }

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        unordered_set<int> tot(a.begin(), a.end());
        tot.insert(b.begin(), b.end());
        tot.insert(0);
        tot.insert((int) 1e9);

        int max_diff = -1e9 - 7;
        int maxd = 0;

        for (int d: tot) {
            int ca = upper_bound(a.begin(), a.end(), d) - a.begin();
            int cb = upper_bound(b.begin(), b.end(), d) - b.begin();
            int diff = cb - ca;

            if (max_diff < diff || (max_diff == diff && d > maxd)) {
                max_diff = diff;
                maxd = d;
                cout << d << endl;
            }
        }

        cout << "#" << t << " " << maxd << endl; 
    }

}