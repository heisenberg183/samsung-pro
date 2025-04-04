#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int main() {    // Time complexity O(n ^ 2), you can reduce it to O(n log n)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("inp.txt", "r", stdin);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n, m;
        cin >> n >> m;
        vector<int> amt(n), inc(n);

        int tamt = 0, tinc = 0;
        vector<pii> growth(n);
        for (int i = 0; i < n; i++) {
            cin >> amt[i];
            cin >> inc[i];
            tamt += amt[i];
            tinc += inc[i];
            // inc for that stock destination and its index
            growth[i] = {inc[i], i};
        }

        // Already satisfied
        if (tamt <= m) {
            cout << "#" << t << " 0" << endl;
            continue;
        }
        
        // It will never reduce the stocks to m
        if (tinc >= m) {
            cout << "#" << t << " -1" << endl;
            continue;
        }

        sort(growth.begin(), growth.end(), [amt](pii a, pii b){
            if (a.first == b.first) { return amt[a.second] < amt[b.second]; }
            return a.first < b.first;
        });

        // for (auto[g, id]: growth) {
        //     cout << "{" << g << ", " << id << "}, ";
        // } cout << endl;

        // Check if reaching m is even possible
        int cumsum = 0; // 0_o
        for (int i = 0; i < n; i++) {
            cumsum += (n - (i + 1)) * growth[i].first;
        }

        // If m is not reached in n days, it will never reach m
        if (cumsum > m) {
            cout << "#" << t << " -1" << endl;
            continue;
        }

        // now begin from the bottom
        int days = n;
        for (; days >= 0; days--) {
            int summ = 0;
            for (int i = 0; i < n - days; i++) {
                summ += (days) * growth[i].first + amt[growth[i].second];
            }
            for (int i = n - days; i < n; i++) {
                summ += (days - (i + 1 - (n - days))) * growth[i].first;
            }
            if (summ > m) {
                days++;
                break;
            }
        }

        cout << "#" << t << " " << days << endl;
    }

    // cout.flush();
}