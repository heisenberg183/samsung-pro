#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("inp.txt", "r", stdin);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;

        array<array<int, 10>, 10> dist = {{0}};
        for (int i = 0; i < n; i++) {
            string num;
            cin >> num;
            int len = num.size();
            int start = num[0] - '0';
            int end = num[len - 1] - '0';
            if (len > dist[start][end]) {
                dist[start][end] = len;
            }
            for (int ch = 0; ch <= 9; ch++) {
                if (dist[ch][start] == 0) { continue; }
                int val = dist[ch][start] + len;
                if (val > dist[ch][end]) {
                    dist[ch][end] = val;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i <= 9; i++) {
            ans = max(ans, dist[i][i]);
        }

        cout << "#" << t << " " << ans << endl; 
    }

}