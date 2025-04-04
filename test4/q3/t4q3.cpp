#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int main() {            // Time complexity O(n)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("inp.txt", "r", stdin);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        
        if (n <= 1) {
            cout << "#" << t << " 0" << endl;
            continue;
        }

        vector<int> stones(n);
        array<vector<int>, 3> cost = {
            vector<int>(n, 0),
            vector<int>(n, 0),
            vector<int>(n, 0),
        };

        for (int i = 0; i < n; i++) {
            cin >> stones[i];
        }
        
        for (int i = 0; i < n; i++) {
            cin >> cost[1][i];          // a[i] 
        }
        for (int i = 0; i < n; i++) {
            cin >> cost[2][i];          // b[i]
        }

        vector<array<int, 2>> dp(n, {{0, 0}});
        int left, right = stones[1];
        dp[0][0] = 0;
        dp[0][1] = cost[right][0];

        for (int i = 1; i < n; i++) {
            if (stones[i] != 1) {
                dp[i][0] = dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]);
                continue;
            }

            left = stones[i - 1];
            right = i < n - 1 && stones[i + 1];
            // case where i+1 is removed first
            dp[i][0] = min(
                dp[i - 1][0] + cost[left][i],
                dp[i - 1][1] + 0
            );
            // case where i is removed first
            dp[i][1] = min(
                dp[i - 1][0] + cost[left + right][i],
                dp[i - 1][1] + cost[right][i]
            );
        }
        
        cout << "#" << t << " " << min(dp[n - 1][0], dp[n - 1][1]) << endl; 
    }

}