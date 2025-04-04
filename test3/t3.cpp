#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int main() {                // Time complexity O(n)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("inp.txt", "r", stdin);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        string s;
        cin >> s;
        // I'm so mad at how good this solution is
        unordered_map<int, int> m;
        m[0] = 0;
        int total = 0, largest = 0;
        for (int i = 0; i < s.size(); i++) {
            total += (s[i] == 'B' ? 1 : -1);
            if (m.find(total) != m.end()) {
                largest = max(
                    largest,
                    i + 1 - m[total]
                );
            } else {
                m[total] = i + 1;
            }
        }
        
        cout << "#" << t << " " << s.size() - largest << endl; 
    }

}