#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int main(int argc, char* argv[]) {      // Time complexity O(n)
    ios_base::sync_with_stdio(false);   // where n = no. of number strings
    cin.tie(NULL);
    freopen("inp.txt", "r", stdin);

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
            
            array<array<int, 10>, 10> temp = dist;
            if (len > temp[start][end]) {
                temp[start][end] = len;
            }

            for (int ch = 0; ch <= 9; ch++) {
                if (dist[ch][start] == 0) { continue; }
                int val = dist[ch][start] + len;
                if (val > temp[ch][end]) {
                    temp[ch][end] = val;
                }
            }

            dist = temp;
        }

        int ans = 0;
        for (int i = 0; i <= 9; i++) {
            ans = max(ans, dist[i][i]);
        }

        cout << "#" << t << " " << ans << endl; 
    }

}